#pragma once

#include <map>
#include <WinSock2.h>

class ClientSession ;
struct Packet ;

class ClientManager
{
public:
	ClientManager() : last_garbage_collect_clock_tick_(0), last_client_work_tick_(0)
	{}

	ClientSession* CreateClient(SOCKET sock) ;
	
	void BroadcastPacket(ClientSession* from, Packet* pkt) ;

	void OnPeriodWork() ;

private:
	void CollectGarbageSessions() ;
	void ClientPeriodWork() ;

private:
	typedef std::map<SOCKET, ClientSession*> ClientList ;
	ClientList	client_list_ ;

	DWORD		last_garbage_collect_clock_tick_ ;
	DWORD		last_client_work_tick_ ;
} ;

extern ClientManager* GClientManager ;