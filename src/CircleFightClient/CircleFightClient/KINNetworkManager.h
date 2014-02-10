#pragma once

#include "KINCommon.h"
#include "CircularBuffer.h"

namespace KIN
{
	namespace Network
	{
		const unsigned int MAX_BUFFER = 1024 * 10;

		class KINNetworkManager
		{
		private:
			SOCKET mSocket;
			string mServerIp;
			unsigned int mServerPort;

		public:
			KINNetworkManager(string pServerIP, unsigned int pServerPort);
			~KINNetworkManager(void);

			bool Init(string pServerIP, unsigned int pServerPort);
			bool SendPacket(CircularBuffer* pSendBuffer);
			bool RecvPacket(CircularBuffer* pRecvBuffer);
		};
	}
}