#pragma once

#include "KINCommon.h"
#include "CircularBuffer.h"

namespace KIN
{
	namespace Network
	{
		const unsigned int MAX_BUFFER = 1024 * 10;

		class KINNM
		{
		private:
			SOCKET mSocket;
			string mServerIp;
			unsigned int mServerPort;

		public:
			KINNM(string pServerIP, unsigned int pServerPort);
			~KINNM(void);

			bool Init(string pServerIP, unsigned int pServerPort);
			bool SendPacket(CircularBuffer* pSendBuffer);
			bool RecvPacket(CircularBuffer* pRecvBuffer);
		};
	}
}