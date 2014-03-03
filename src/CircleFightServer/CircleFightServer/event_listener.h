#pragma once
#include "event.h"
class EventListener
{
public:
	EventListener(void);
	virtual ~EventListener(void);
	virtual void Notify(EventHeader& event) = 0;
};

