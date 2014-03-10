#pragma once

#include "Config.h"
#include "..\..\PacketType\packet_type.pb.h"
#include "circular_buffer.h"
#include <map>
#include <WinSock2.h>

#define BUFSIZE	(1024*10)
class ClientSession ;
class ClientManager ;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO() :object_(nullptr)
	{}

	ClientSession* object_ ;
} ;

class ClientSession
{
public:
	ClientSession(SOCKET sock)
		: is_connected_(false), is_log_on_(false), socket_(sock), player_id_(-1), send_buffer_(BUFSIZE), recv_buffer_(BUFSIZE), is_overlapped_requested_(0)
		
	{
		memset(&client_address_, 0, sizeof(SOCKADDR_IN)) ;
	}
	~ClientSession() {}


	
	void	OnRead(size_t len) ;
	void	OnWriteComplete(size_t len) ;

	bool	OnConnect(SOCKADDR_IN* addr) ;
	
	bool	PostRecv() ;

	bool	Send() ;
	bool	Broadcast(Packet* pkt) ;
	bool	BroadcastWithoutMe(Packet* pkt);
	bool	Write(Packet* pkt);

	void	Disconnect() ;

	bool	IsConnected() const { return is_connected_ ; }


	/// 현재 Send/Recv 요청 중인 상태인지 검사하기 위함
	void	IncOverlappedRequest()		{ ++is_overlapped_requested_ ; }
	void	DecOverlappedRequest()		{ --is_overlapped_requested_ ; }
	bool	DoingOverlappedOperation() const { return is_overlapped_requested_ > 0 ; }

	short GetPlayerID(){ return player_id_; }
private:
	void	OnTick() ;

	void	UpdateDone() ;
	
	void	SetPlayerID(short player_id)	{ player_id_ = player_id; }

private:
	bool			is_connected_ ;
	bool			is_log_on_ ;
	SOCKET			socket_ ;

	int				player_id_ ;
	SOCKADDR_IN		client_address_ ;

	CircularBuffer	send_buffer_ ;
	CircularBuffer	recv_buffer_ ;

	OverlappedIO	overlapped_send_ ;
	OverlappedIO	overlapped_recv_ ;
	int				is_overlapped_requested_ ;

	friend class ClientManager ;
	friend void LoginRequestHandler(ClientSession* client_session_, LoginRequest in_packet);
} ;




void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
