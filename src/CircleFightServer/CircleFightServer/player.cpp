#include "player.h"
#include	"event_manager.h"

Player::Player()
{
	g_event_manager->AddEventListener(EVENT_MOVE,object_id_);
	g_event_manager->AddEventListener(EVENT_KEY_CHANGE,object_id_);
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
		if( CouldTransState( MOVE ) == true )
		{
			TransState( MOVE );
			position_ = move_event.start_position_;
			velocity_ = move_event.move_velocity_;
		}
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

