#pragma once
#include "definition.h"
#include <memory>
enum EventTypes
{
	EVENT_NO	= 0,

	EVENT_LOGIN,
	EVENT_MOVE,
	EVENT_MOVE_KEY_CHANGE,
	EVENT_MOVE_STOP	,
	EVENT_HP_CHANGE,
	EVENT_HIT,
	EVENT_ATTACK_KEY_CHANGE,
} ;

struct EventHeader
{
	EventTypes event_type_;
	ObjectID event_sender_id_;
};

struct LoginEvent
	: public EventHeader
{

};

struct MoveEvent
	: public EventHeader
{
	MoveEvent(){
		event_type_ = EVENT_MOVE;
		start_position_ = Point();
		move_velocity_ = Point();
	}
	ObjectID object_move_;
	Point start_position_;
	Point move_velocity_;
};

struct MoveKeyChangeEvent
	: public EventHeader
{
	MoveKeyChangeEvent(){
		event_type_ = EVENT_MOVE_KEY_CHANGE;
		memset(&move_keys_,0,sizeof(move_keys_));
	}
	ObjectID object_id_chnaged_;
	MoveKey move_keys_;	
};

struct HPChangeEvent
	: public EventHeader
{
	HPChangeEvent(){
		event_type_ = EVENT_HP_CHANGE;
	}

	ObjectID object_id_changed_;
	int hp_;
};

struct HitEvent
	: public EventHeader
{
	HitEvent(){
		event_type_ = EVENT_HIT;
	}

	ObjectID object_id_hit_;
	int damage_;
};

struct AttackKeyChangeEvent
	: public EventHeader
{
	AttackKeyChangeEvent(){
		event_type_ = EVENT_ATTACK_KEY_CHANGE;
	}

	ObjectID object_id_changed_;
	AttackKey attack_key_;
};

struct MoveStopEvent
	: public EventHeader
{
	MoveStopEvent(){
		event_type_ = EVENT_MOVE_STOP;
	}

	ObjectID object_id_stoped;
};