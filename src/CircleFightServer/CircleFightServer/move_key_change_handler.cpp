#include "stdafx.h"
#include "move_key_chnage_handler.h"
#include "event_manager.h"

void MoveKeyChangeHandler(ClientSession* client_session_, MoveKeyPressRequest in_packet)
{
	MoveKeyChangeEvent move_key_event;
	move_key_event.move_keys_.key_move_up_ = in_packet.move_key_w_press();
	move_key_event.move_keys_.key_move_left_ = in_packet.move_key_a_press();
	move_key_event.move_keys_.key_move_down_ = in_packet.move_key_s_press();
	move_key_event.move_keys_.key_move_right_ = in_packet.move_key_d_press();
	
	move_key_event.object_id_chnaged_ = client_session_->GetPlayerID();
	printf("%d %d %d %d\n",move_key_event.move_keys_.key_move_up_,
		move_key_event.move_keys_.key_move_left_,
		move_key_event.move_keys_.key_move_down_,
		move_key_event.move_keys_.key_move_right_);
	g_event_manager->Notify(move_key_event);
}