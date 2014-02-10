#include "KINNetworkManager.h"
#include "ProcessPacket.h"

namespace KIN
{
	namespace Network
	{
		KINNetworkManager::KINNetworkManager(string pServerIP, unsigned int pServerPort)
		{
			assert(Init(pServerIP, pServerPort));
		}
		KINNetworkManager::~KINNetworkManager(void)
		{
		}

		bool KINNetworkManager::Init(string pServerIP, unsigned int pServerPort)
		{
			int nReturn = 0;

			WSADATA WSAData;
			sockaddr_in Sock_Addr = { 0, };
			int Addr_Lenght = sizeof(Sock_Addr);

			nReturn = WSAStartup(MAKEWORD(2,2), &WSAData);
			if(nReturn != 0)
			{
				printf("Error : WSAStartup() : %d\n", WSAGetLastError());
				return false;
			}

			mSocket = socket(AF_INET, SOCK_STREAM, 0);
			if(mSocket == INVALID_SOCKET)
			{
				printf("Error : socket() : %d\n", WSAGetLastError());
				return false;
			}

			Sock_Addr.sin_family = AF_INET;
			Sock_Addr.sin_addr.s_addr = inet_addr(pServerIP.c_str());
			Sock_Addr.sin_port = htons(pServerPort);

			nReturn = connect(mSocket, (sockaddr*)&Sock_Addr, Addr_Lenght);
			if(nReturn == SOCKET_ERROR)
			{
				printf("Error : connect() : %d\n", WSAGetLastError());
				return false;
			}

			DWORD ThreadId;
			HANDLE ThreadHandle;

			ThreadHandle = CreateThread(NULL, 0, ProcessPacket, this, 0, &ThreadId);

			mServerIp = pServerIP;
			mServerPort = pServerPort;

			return true;
		}

		bool KINNetworkManager::SendPacket(CircularBuffer* pSendBuffer)
		{
			int size = pSendBuffer->GetStoredSize();
			if(size > 0)
			{
				char* data = new char[size];
				pSendBuffer->Peek(data, size);

				int sent = send(mSocket, data, size, 0);
				pSendBuffer->Remove(sent);

				delete [] data;

				if(sent != size)
				{
					OutputDebugStringA("sent != request\n") ;
					return false;
				}

				return true;
			}

			return false;
		}

		bool KINNetworkManager::RecvPacket(CircularBuffer* pRecvBuffer)
		{
			char inBuf[MAX_BUFFER] = {0, } ;
					
			int recvLen = recv(mSocket, inBuf, MAX_BUFFER, 0) ;
			
			if(SOCKET_ERROR == recvLen || recvLen == 0)
			{
				return false;
			}

			if (!pRecvBuffer->Write(inBuf, recvLen))
			{
				assert(false) ;
			}
					
			// ProcessPacket

			return true;
		}
	}
}