#pragma once
#include "definition.h"
enum EventTypes
{
	EVENT_NO	= 0,

	EVENT_LOGIN	= 1,
	EVENT_MOVE	= 2,
	EVENT_KEY_CHANGE = 3,
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
	Point start_position_;
	Point move_velocity_;
};

struct KeyChangeEvent
	: public EventHeader
{
	Key keys_;	
};