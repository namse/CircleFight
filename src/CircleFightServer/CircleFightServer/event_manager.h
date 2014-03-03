#pragma once
#include "event.h"
#include "event_listener.h"
#include <map>
class EventManager
{
public:
	EventManager(void);
	~EventManager(void);

	void AddEventListener(EventTypes event_type, ObjectID object_id);
	void RemoveEventListener(EventTypes event_type, ObjectID object_id);
	void RemoveEventListener(ObjectID object_id);
	void Notify(EventHeader& event);



private:
	std::multimap<EventTypes, ObjectID> event_listener_list;


};


extern EventManager* g_event_manager;