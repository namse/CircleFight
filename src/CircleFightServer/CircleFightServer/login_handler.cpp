#include "stdafx.h"
#include "login_handler.h"
#include "object_manager.h"
#include "player.h"

void LoginRequestHandler(ClientSession* client_session_, LoginRequest in_packet)
{

	Player* player = new Player();

	g_object_manager->AddObject(player);
	
	short id = (short)player->GetObjectID();

	client_session_->SetPlayerID( id );
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
		client_session_->BroadcastWithoutMe(&out_packet );
	}
}