#include "player.h"
#include	"event_manager.h"
#include "client_manager.h"
#include "Config.h"

Player::Player():state_(IDLE)
{
	g_event_manager->AddEventListener( EVENT_MOVE, object_id_ );
	g_event_manager->AddEventListener( EVENT_MOVE_KEY_CHANGE, object_id_ );
	g_event_manager->AddEventListener( EVENT_HP_CHANGE, object_id_ );
	g_event_manager->AddEventListener( EVENT_HIT, object_id_ );
	g_event_manager->AddEventListener( EVENT_ATTACK_KEY_CHANGE, object_id_ );
	g_event_manager->AddEventListener( EVENT_MOVE_STOP, object_id_ );
}


Player::~Player(void)
{

}

void Player::Update(float d_time)
{

	switch (state_)
	{
	case IDLE:
		{

		}break;
	case MOVE:
		{
			position_ = position_ + velocity_ * 100 * d_time;
			printf("%.1f, %.1f %d \n",position_.x_, position_.y_, state_);
		}break;
	default:
		break;
	}
}

void Player::Notify(EventHeader& event)
{
	switch (event.event_type_)//(EventTypes)
	{
	case EVENT_NO:
		break;
	case EVENT_MOVE:
		{
			MoveEvent& move_event = (MoveEvent &)(event);
			if( move_event.object_move_ == object_id_ && CouldTransState( MOVE ) == true )
			{
				TransState( MOVE );
				position_ = move_event.start_position_;
				velocity_ = move_event.move_velocity_;

				//send packet
				MoveResult out_packet_content;
				out_packet_content.set_player_id(object_id_);
				out_packet_content.set_position_x(position_.x_);
				out_packet_content.set_position_y(position_.y_);
				out_packet_content.set_velocity_x(velocity_.x_);
				out_packet_content.set_velocity_y(velocity_.y_);

				Packet out_packet = Packet(PKT_SC_MOVE_START, &out_packet_content);
				g_client_manager->BroadcastPacket(&out_packet);
			}
		}break;
	case EVENT_MOVE_KEY_CHANGE:
		{
			MoveKeyChangeEvent& move_key_change_event = (MoveKeyChangeEvent &)(event);
			if( move_key_change_event.object_id_chnaged_ == object_id_)
			{

				Point velocity = Point();
				if( move_key_change_event.move_keys_.key_move_up_ == true )
					velocity.y_ += 1.f;
				if( move_key_change_event.move_keys_.key_move_down_ == true )
					velocity.y_ -= 1.f;
				if( move_key_change_event.move_keys_.key_move_left_ == true )
					velocity.x_ -= 1.f;
				if( move_key_change_event.move_keys_.key_move_right_ == true )
					velocity.x_ += 1.f;
				if( velocity.Length() > 1.f )
					velocity = velocity / pow(2, 0.5);

				if( velocity.Length() == 0.f && CouldTransState( IDLE ) )
				{
					MoveStopEvent move_stop_event = MoveStopEvent();
					move_stop_event.object_id_stoped = object_id_;
					move_stop_event.event_sender_id_ = object_id_;
					g_event_manager->Notify( move_stop_event );
				}

				else if( CouldTransState( MOVE ) == true)
				{

					MoveEvent move_event = MoveEvent();
					move_event.event_sender_id_ = object_id_;
					move_event.move_velocity_ = velocity;
					move_event.start_position_ = position_;
					move_event.object_move_ = object_id_;
					g_event_manager->Notify( move_event );
				}
			}
		}break;
	case EVENT_HP_CHANGE:
		{
			HPChangeEvent& hp_change_event = (HPChangeEvent &)(event);

			if( hp_change_event.object_id_changed_ == object_id_ )
			{
				hp_ = hp_change_event.hp_;

				//send packet
			}
		}break;

	case EVENT_HIT:
		{
			HitEvent& hit_event = (HitEvent &)(event);

			if( hit_event.object_id_hit_ == object_id_ )
			{
				//TODO

				if( hp_ <= hit_event.damage_ )
				{
					//TODO
					//1. make state DIE
					//2. make events
					//3. make packet
				}

				else if( hp_ > hit_event.damage_ )
				{
					HPChangeEvent hp_change_event = HPChangeEvent();
					hp_change_event.hp_ = hp_ - hit_event.damage_;
					hp_change_event.event_sender_id_ = hp_change_event.object_id_changed_ = object_id_;
					g_event_manager->Notify(hp_change_event);
				}
			}
		}break;

	case EVENT_ATTACK_KEY_CHANGE:
		{
			AttackKeyChangeEvent& attack_key_change_event = (AttackKeyChangeEvent &)(event);

			if( attack_key_change_event.object_id_changed_ = object_id_ )
			{
				//TODO
				if( attack_key_change_event.attack_key_.key_attack_mouse_left == true )
				{
					//accroding to weapon types,

					//for default
					//TODO
					//1. make bullet
					//2. shoot it.
				}
			}
		}break;

	case EVENT_MOVE_STOP:
		{
			MoveStopEvent& move_stop_event = (MoveStopEvent &)(event);

			if( move_stop_event.object_id_stoped == object_id_ && CouldTransState( IDLE ) == true)
			{
				TransState( IDLE );
				velocity_ = Point(0,0);

				//Send NowPosition To server
				MoveStopResult out_packet_content;
				out_packet_content.set_player_id(object_id_);
				out_packet_content.set_position_x(position_.x_);
				out_packet_content.set_position_y(position_.y_);

				Packet out_packet = Packet(PKT_SC_MOVE_STOP, &out_packet_content);
				g_client_manager->BroadcastPacket(&out_packet);

			}
		}break;
	default:
		break;
	}
}

bool Player::CouldTransState(const State to_state)
{
	switch (state_)
	{
	case IDLE:
		{
			return true;
		}break;
	case MOVE:
		{
			return true;
		}break;
	default:
		break;
	}
}
void Player::TransState(const State to_state)
{
	//Before
	switch (state_)
	{
	case IDLE:
		break;
	case MOVE:
		break;
	default:
		break;
	}

	//Now, Trans
	switch (to_state)
	{
	case IDLE:
		{
			velocity_ = Point(0,0);
		}break;
	case MOVE:
		{

		}break;
	default:
		break;
	}


	state_ = to_state;
}

