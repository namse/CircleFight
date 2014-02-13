#pragma once

#include "Config.h"
#include "..\..\PacketType.h"
#include "CircularBuffer.h"
#include <map>
#include <WinSock2.h>

#define BUFSIZE	(1024*10)
class ClientSession ;
class ClientManager ;

struct OverlappedIO : public OVERLAPPED
{
	OverlappedIO() :mObject(nullptr)
	{}

	ClientSession* mObject ;
} ;

class ClientSession
{
public:
	ClientSession(SOCKET sock)
		: mConnected(false), mLogon(false), mSocket(sock), mPlayerId(-1), mSendBuffer(BUFSIZE), mRecvBuffer(BUFSIZE), mOverlappedRequested(0)
		
	{
		memset(&mClientAddr, 0, sizeof(SOCKADDR_IN)) ;
	}
	~ClientSession() {}


	
	void	OnRead(size_t len) ;
	void	OnWriteComplete(size_t len) ;

	bool	OnConnect(SOCKADDR_IN* addr) ;
	
	bool	PostRecv() ;

	bool	Send(PacketHeader* pkt) ;
	bool	Broadcast(PacketHeader* pkt) ;

	void	Disconnect() ;

	bool	IsConnected() const { return mConnected ; }


	/// ���� Send/Recv ��û ���� �������� �˻��ϱ� ����
	void	IncOverlappedRequest()		{ ++mOverlappedRequested ; }
	void	DecOverlappedRequest()		{ --mOverlappedRequested ; }
	bool	DoingOverlappedOperation() const { return mOverlappedRequested > 0 ; }

private:
	void	OnTick() ;

	void	LoginDone(int pid, double x, double y, double z, const char* name) ;
	void	UpdateDone() ;


private:
	bool			mConnected ;
	bool			mLogon ;
	SOCKET			mSocket ;

	int				mPlayerId ;
	SOCKADDR_IN		mClientAddr ;

	CircularBuffer	mSendBuffer ;
	CircularBuffer	mRecvBuffer ;

	OverlappedIO	mOverlappedSend ;
	OverlappedIO	mOverlappedRecv ;
	int				mOverlappedRequested ;

	friend class ClientManager ;
} ;




void CALLBACK RecvCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
void CALLBACK SendCompletion(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) ;
