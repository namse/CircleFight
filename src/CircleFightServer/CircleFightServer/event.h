#pragma once
#include "definition.h"
#include <memory>
enum EventTypes
{
	EVENT_NO	= 0,

	EVENT_LOGIN	= 1,
	EVENT_MOVE	= 2,
	EVENT_MOVE_KEY_CHANGE = 3,
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

	MoveKey move_keys_;	
};