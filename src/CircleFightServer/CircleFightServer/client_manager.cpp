#include "stdafx.h"
#include "main.h"
#include "packet_type.pb.h"
#include "client_session.h"
#include "client_manager.h"
#include "object_manager.h"

ClientManager* g_client_manager = nullptr ;

ClientSession* ClientManager::CreateClient(SOCKET sock)
{
	ClientSession* client = new ClientSession(sock) ;
	client_list_.insert(ClientList::value_type(sock, client)) ;

	return client ;
}



void ClientManager::BroadcastPacket(ClientSession* from, Packet* pkt)
{
	///FYI: C++ STL iterator ��Ÿ���� ����
	for (ClientList::const_iterator it=client_list_.begin() ; it!=client_list_.end() ; ++it)
	{
		ClientSession* client = it->second ;
		
		if ( from == client )
			continue ;
		
		client->Write(pkt) ;
	}
}

void ClientManager::OnPeriodWork()
{
	static DWORD previous_tick = 0;

	/// ������ ���� ���ǵ� �ֱ������� ���� (1�� ���� ���� ������)
	DWORD current_tick = GetTickCount() ;
	if ( current_tick - last_garbage_collect_clock_tick_ >= 1000 )
	{
		CollectGarbageSessions() ;
		last_garbage_collect_clock_tick_ = current_tick ;
	}

	/// ���ӵ� Ŭ���̾�Ʈ ���Ǻ��� �ֱ������� ����� �ϴ� �� (�ֱ�� �˾Ƽ� ���ϸ� �� - ������ 1�ʷ� ����)
	if ( current_tick - last_client_work_tick_ >= 1000 )
	{
		ClientPeriodWork() ;
		last_client_work_tick_ = current_tick ;
	}

	g_object_manager->Update( current_tick - previous_tick );

	previous_tick = current_tick;
}

void ClientManager::CollectGarbageSessions()
{
	std::vector<ClientSession*> disconnectedSessions ;
	
	///FYI: C++ 11 ���ٸ� �̿��� ��Ÿ��
	std::for_each(client_list_.begin(), client_list_.end(),
		[&](ClientList::const_reference it)
		{
			ClientSession* client = it.second ;

			if ( false == client->IsConnected() && false == client->DoingOverlappedOperation() )
				disconnectedSessions.push_back(client) ;
		}
	) ;
	

	///FYI: C��� ��Ÿ���� ����
	for (size_t i=0 ; i<disconnectedSessions.size() ; ++i)
	{
		ClientSession* client = disconnectedSessions[i] ;
		client_list_.erase(client->socket_) ;
		delete client ;
	}

}

void ClientManager::ClientPeriodWork()
{
	/// FYI: C++ 11 ��Ÿ���� ����
	for (auto& it : client_list_)
	{
		ClientSession* client = it.second ;
		client->OnTick() ;
	}
}
