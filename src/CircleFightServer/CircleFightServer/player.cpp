#include "player.h"
#include	"event_manager.h"

Player::Player():state_(IDLE)
{
	g_event_manager->AddEventListener(EVENT_MOVE,object_id_);
	g_event_manager->AddEventListener(EVENT_MOVE_KEY_CHANGE,object_id_);
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
	if( event.event_type_ == EVENT_MOVE )
	{
		MoveEvent& move_event = (MoveEvent &)(event);
		if( move_event.object_move_ == object_id_ && CouldTransState( MOVE ) == true )
		{
			TransState( MOVE );
			position_ = move_event.start_position_;
			velocity_ = move_event.move_velocity_;
		}
	}
	if( event.event_type_ == EVENT_MOVE_KEY_CHANGE )
	{
		MoveKeyChangeEvent& move_key_change_event = (MoveKeyChangeEvent &)(event);

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

		MoveEvent move_event = MoveEvent();
		move_event.event_sender_id_ = object_id_;
		move_event.move_velocity_ = velocity;
		move_event.start_position_ = position_;
		move_event.object_move_ = object_id_;
		g_event_manager->Notify( move_event );
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
	case MOVE:
		{
			state_ = to_state;
		}break;
	default:
		break;
	}
}

