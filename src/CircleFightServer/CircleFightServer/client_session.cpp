#include "stdafx.h"
#include "client_session.h"
#include "packet_type.pb.h"
#include "client_manager.h"
#include "packet_parse.h"

bool ClientSession::OnConnect(SOCKADDR_IN* addr)
{
	memcpy(&client_address_, addr, sizeof(SOCKADDR_IN)) ;

	/// 소켓을 넌블러킹으로 바꾸고
	u_long arg = 1 ;
	::ioctlsocket(socket_, FIONBIO, &arg) ;

	/// nagle 알고리즘 끄기
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

	/// 비동기 입출력 시작
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

	/// 패킷 파싱하고 처리
	if( ParsePacket(this,recv_buffer_) == false)
		Disconnect() ;
}

bool ClientSession::Send()
{
	if ( !IsConnected() )
		return false ;


	/// 보낼 데이터가 있는지 검사
	if ( send_buffer_.GetContiguiousBytes() == 0 )
	{
		/// 방금전에 write 했는데, 데이터가 없다면 뭔가 잘못된 것
		return false ;
	}

	DWORD send_bytes = 0 ;
	DWORD flags = 0 ;

	WSABUF buf ;
	buf.len = (ULONG)send_buffer_.GetContiguiousBytes() ;
	buf.buf = (char*)send_buffer_.GetBufferStart() ;

	memset(&overlapped_send_, 0, sizeof(OverlappedIO)) ;
	overlapped_send_.object_ = this ;

	// 비동기 입출력 시작
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
	/// 보내기 완료한 데이터는 버퍼에서 제거
	send_buffer_.Remove(len) ;

	/// 얼래? 덜 보낸 경우도 있나? (커널의 send queue가 꽉찼거나, Send Completion이전에 또 send 한 경우?)
	if ( send_buffer_.GetContiguiousBytes() > 0 )
	{
		assert(false) ;
	}

}

bool ClientSession::Broadcast(Packet* pkt)
{
	if ( !Write(pkt) )
		return false ;

	return BroadcastWithoutMe(pkt);
}

bool ClientSession::BroadcastWithoutMe(Packet* pkt)
{

	if ( !IsConnected() )
		return false ;

	g_client_manager->BroadcastPacket(this, pkt) ;

	return true ;
}

bool ClientSession::Write(Packet* pkt)
{
	/// 버퍼 용량 부족인 경우는 끊어버림
	if ( false == send_buffer_.Write((char*)pkt, pkt->packet_header_.size_) )
	{
		Disconnect() ;
		return false ;
	}
}




void ClientSession::OnTick()
{
	/// 클라별로 주기적으로 해야될 일은 여기에

}
void ClientSession::UpdateDone()
{
	/// 콘텐츠를 넣기 전까지는 딱히 해줄 것이 없다. 단지 테스트를 위해서..
	printf("DEBUG: Player[%d] Update Done\n", player_id_) ;
}




///////////////////////////////////////////////////////////

void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags)
{
	ClientSession* from_client = static_cast<OverlappedIO*>(lpOverlapped)->object_ ;

	from_client->DecOverlappedRequest() ;

	if ( !from_client->IsConnected() )
		return ;

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		from_client->Disconnect() ;
		return ;
	}

	/// 받은 데이터 처리
	from_client->OnRead(cbTransferred) ;

	/// 다시 받기
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

	/// 에러 발생시 해당 세션 종료
	if ( dwError || cbTransferred == 0 )
	{
		from_client->Disconnect() ;
		return ;
	}

	from_client->OnWriteComplete(cbTransferred) ;

}

