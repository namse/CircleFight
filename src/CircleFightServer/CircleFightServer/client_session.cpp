#include "stdafx.h"
#include "client_session.h"
#include "..\..\PacketType\packet_type.pb.h"
#include "client_manager.h"

bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	memcpy(&client_address_, addr, sizeof(SOCKADDR_IN)) ;

	/// ������ �ͺ�ŷ���� �ٲٰ�
	u_long arg = 1 ;
	::ioctlsocket(socket_, FIONBIO, &arg) ;

	/// nagle �˰��� ����
	int opt = 1 ;
	::setsockopt(socket_, IPPROTO_TCP, TCP_NODELAY, (const char*)&opt, sizeof(int)) ;

	printf("[DEBUG] Client Connected: IP=%s, PORT=%d\n", inet_ntoa(client_address_.sin_addr), ntohs(client_address_.sin_port)) ;
	
	is_connected_ = true ;

	return PostRecv() ;
}

bool ClientSession::PostRecv()
{
	if ( !IsConnected() )
		return false ;

	DWORD recvbytes = 0 ;
	DWORD flags = 0 ;
	WSABUF buf ;
	buf.len = (ULONG)recv_buffer_.GetFreeSpaceSize() ;
	buf.buf = (char*)recv_buffer_.GetBuffer() ;

	memset(&overlapped_recv_, 0, sizeof(OverlappedIO)) ;
	overlapped_recv_.object_ = this ;

	/// �񵿱� ����� ����
	if ( SOCKET_ERROR == WSARecv(socket_, &buf, 1, &recvbytes, &flags, &overlapped_recv_, RecvCompletion) )
	{
		if ( WSAGetLastError() != WSA_IO_PENDING )
			return false ;
	}

	IncOverlappedRequest() ;

	return true ;
}

void ClientSession::Disconnect()
{
	if ( !IsConnected() )
		return ;

	printf("[DEBUG] Client Disconnected: IP=%s, PORT=%d\n", inet_ntoa(client_address_.sin_addr), ntohs(client_address_.sin_port)) ;

	::shutdown(socket_, SD_BOTH) ;
	::closesocket(socket_) ;

	is_connected_ = false ;
}


void ClientSession::OnRead(size_t len)
{
	recv_buffer_.Commit(len) ;

	/// ��Ŷ �Ľ��ϰ� ó��
	while ( true )
	{
		/// ��Ŷ ��� ũ�� ��ŭ �о�ͺ���
		PacketHeader header;
		if ( false == recv_buffer_.Peek((char*)&header, sizeof(PacketHeader)) )
			return ;

		/// ��Ŷ �ϼ��� �Ǵ°�? 
		if ( recv_buffer_.GetStoredSize() < (header.size() - sizeof(PacketHeader)) )
			return ;
		/// ��Ŷ �ڵ鸵
		switch ( header.type() )
		{
		case PKT_CS_LOGIN:
			{
				LoginRequest in_packet ;
				recv_buffer_.Read((char*)&in_packet, header.size()) ;
			
			}
			break ;

		default:
			{
				/// ���� ������ �̻��� ��Ŷ �����Ŵ�.
				Disconnect() ;
				return ;
			}
			break ;
		}
	}
}

bool ClientSession::Send(PacketHeader* pkt)
{
	if ( !IsConnected() )
		return false ;

	/// ���� �뷮 ������ ���� �������
	if ( false == send_buffer_.Write((char*)pkt, pkt->size()) )
	{
		Disconnect() ;
		return false ;
	}

	/// ���� �����Ͱ� �ִ��� �˻�
	if ( send_buffer_.GetContiguiousBytes() == 0 )
	{
		/// ������� write �ߴµ�, �����Ͱ� ���ٸ� ���� �߸��� ��
		assert(false) ;
		Disconnect() ;
		return false ;
	}
		
	DWORD send_bytes = 0 ;
	DWORD flags = 0 ;

	WSABUF buf ;
	buf.len = (ULONG)send_buffer_.GetContiguiousBytes() ;
	buf.buf = (char*)send_buffer_.GetBufferStart() ;
	
	memset(&overlapped_send_, 0, sizeof(OverlappedIO)) ;
	overlapped_send_.object_ = this ;

	// �񵿱� ����� ����
	if ( SOCKET_ERROR == WSASend(socket_, &buf, 1, &send_bytes, flags, &overlapped_send_, SendCompletion) )
	{
		if ( WSAGetLastError() != WSA_IO_PENDING )
			return false ;
	}

	IncOverlappedRequest() ;
	return true ;
}

void ClientSession::OnWriteComplete(size_t len)
{
	/// ������ �Ϸ��� �����ʹ� ���ۿ��� ����
	send_buffer_.Remove(len) ;

	/// ��? �� ���� ��쵵 �ֳ�? (Ŀ���� send queue�� ��á�ų�, Send Completion������ �� send �� ���?)
	if ( send_buffer_.GetContiguiousBytes() > 0 )
	{
		assert(false) ;
	}

}

bool ClientSession::Broadcast(PacketHeader* pkt)
{
	if ( !Send(pkt) )
		return false ;

	if ( !IsConnected() )
		return false ;

	GClientManager->BroadcastPacket(this, pkt) ;

	return true ;
}

void ClientSession::OnTick()
{
	/// Ŭ�󺰷� �ֱ������� �ؾߵ� ���� ���⿡

}
void ClientSession::UpdateDone()
{
	/// �������� �ֱ� �������� ���� ���� ���� ����. ���� �׽�Ʈ�� ���ؼ�..
	printf("DEBUG: Player[%d] Update Done\n", player_id_) ;
}




///////////////////////////////////////////////////////////

void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* from_client = static_cast<OverlappedIO*>(lpOverlapped)->object_ ;
	
	from_client->DecOverlappedRequest() ;

	if ( !from_client->IsConnected() )
		return ;

	/// ���� �߻��� �ش� ���� ����
	if ( dwError || cbTransferred == 0 )
	{
		from_client->Disconnect() ;
		return ;
	}

	/// ���� ������ ó��
	from_client->OnRead(cbTransferred) ;

	/// �ٽ� �ޱ�
	if ( false == from_client->PostRecv() )
	{
		from_client->Disconnect() ;
		return ;
	}
}


void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* from_client = static_cast<OverlappedIO*>(lpOverlapped)->object_ ;

	from_client->DecOverlappedRequest() ;

	if ( !from_client->IsConnected() )
		return ;

	/// ���� �߻��� �ش� ���� ����
	if ( dwError || cbTransferred == 0 )
	{
		from_client->Disconnect() ;
		return ;
	}

	from_client->OnWriteComplete(cbTransferred) ;

}

