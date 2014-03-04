#include "stdafx.h"
#include "login_handler.h"

void LoginRequestHandler(ClientSession* client_session_, LoginRequest in_packet)
{
	short id = rand()%10;

	{
		LoginResult out_packet_content;
		out_packet_content.set_player_id(id); //test

		Packet out_packet = Packet(PKT_SC_LOGIN, &out_packet_content);
		client_session_->Write( &out_packet );
	}

	{
		LoginBroadcastResult out_packet_content;
		out_packet_content.set_player_id(id);

		Packet out_packet = Packet(PKT_SC_LOGIN_BROADCAST, &out_packet_content);
		client_session_->Broadcast( &out_packet );
	}
}