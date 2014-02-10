#include "KINNM.h"
#include "ProcessPacket.h"
#include "CircularBuffer.h"
#include "..\..\PacketType.h"

using namespace KIN::Network;

DWORD WINAPI ProcessPacket(void* param)
{
	KINNM* Server =(KINNM*)param;

	printf("ProcessPacket Start.\n");

	while(true)
	{
		PacketHeader header;

		CircularBuffer* RecvBuffer = new CircularBuffer(MAX_BUFFER);
		while(Server->RecvPacket(RecvBuffer) == false);

		if(false == RecvBuffer->Peek((char*)&header, sizeof(PacketHeader)))
			break;

		if(header.mSize > RecvBuffer->GetStoredSize())
			break;

		//switch(header.mType)
		//{
		//case PKT_SC_LOGIN:
		//	{
		//		LoginResult recvData;
		//		if(g_RecvBuffer.Read((char*)&recvData, header.mSize))
		//		{
		//			// 패킷처리
		//			if(recvData.mPlayerId == -1 )
		//			{
		//				/// 여기 걸리면 로그인 실패다.
		//				ExitProcess(-1);
		//			}
		//			

		//			g_MyClientId = recvData.mPlayerId;
		//			g_LoginComplete = true;
		//		
		//			char buff[128] = {0, };
		//			sprintf_s(buff, "LOGIN SUCCESS ClientId[%d] Name[%s] POS(%.4f, %.4f, %.4f) \n", g_MyClientId, recvData.mName, recvData.mPosX, recvData.mPosY, recvData.mPosZ);

		//			static int ypos = 33;
		//			HDC hdc = GetDC(hWnd);
		//			TextOutA(hdc, 10, 33, buff, strlen(buff));
		//			ReleaseDC(hWnd, hdc);

		//			/// 채팅 방송 패킷 보내는 타이머 돌리자.. 
		//			SetTimer(hWnd, 337, 100, NULL);
		//		
		//		}
		//		else
		//		{
		//			assert(false);
		//		}

		//		break;
		//	}

		//case PKT_SC_CHAT:
		//	{
		//		ChatBroadcastResult recvData;
		//		if(g_RecvBuffer.Read((char*)&recvData, header.mSize))
		//		{
		//			/// 여기 걸리면 로그인 안된놈이 보낸거다
		//			assert(recvData.mPlayerId != -1 );

		//			char buff[MAX_CHAT_LEN] = {0, };
		//			sprintf_s(buff, "CHAT from Player[%s]: %s \n", recvData.mName, recvData.mChat);

		//			static int y2pos = 60;
		//			HDC hdc = GetDC(hWnd);
		//			TextOutA(hdc, 10, y2pos, buff, strlen(buff));
		//			ReleaseDC(hWnd, hdc);
		//			y2pos += 15;
		//			if(y2pos > 600)
		//				y2pos = 60;
		//			
		//		}
		//		else
		//		{
		//			assert(false);
		//		}

		//		break;
		//	}

		//default:
		//	{
		//		assert(false);
		//	}
		//}
	}

	return 0;
}