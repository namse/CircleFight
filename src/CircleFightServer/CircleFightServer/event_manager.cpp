#include "event_manager.h"
#include "object_manager.h"

EventManager::EventManager(void)
{
}


EventManager::~EventManager(void)
{
}


void EventManager::AddEventListener(EventTypes event_type, ObjectID object_id)
{
	event_listener_list.insert( std::pair<EventTypes, ObjectID>(event_type, object_id) );
}
void EventManager::RemoveEventListener(EventTypes event_type, ObjectID object_id)
{	
	typedef std::multimap<EventTypes, ObjectID>::iterator iterator;
	std::pair<iterator, iterator> iterpair = event_listener_list.equal_range(event_type);

	iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
		if (it->second == object_id) { 
			event_listener_list.erase(it);
			break;
		}
	}
	
}
void EventManager::RemoveEventListener(ObjectID object_id)
{
	for (auto it = event_listener_list.begin(); it != event_listener_list.end(); ) {
		if (it->second == object_id)
			it = event_listener_list.erase(it);
		else
			++it;
	}
}

void EventManager::Notify(EventHeader& event)
{
	typedef std::multimap<EventTypes, ObjectID>::iterator iterator;
	std::pair<iterator, iterator> iterpair = event_listener_list.equal_range(event.event_type_);

	iterator it = iterpair.first;
	for (; it != iterpair.second; ++it) {
		g_object_manager->GetObject(it->second)->Notify(event);
	}
}

EventManager *g_event_manager = nullptr;