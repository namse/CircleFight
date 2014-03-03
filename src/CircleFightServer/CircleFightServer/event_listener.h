#pragma once
#include "event.h"
class EventListener
{
public:
	EventListener(void);
	virtual ~EventListener(void);
	virtual void notify(const EventHeader& event) = 0;
};

