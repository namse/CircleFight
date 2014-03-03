#include "object.h"
#include "object_manager.h"

Object::Object()
{
	g_object_manager->AddObject(this);
}


Object::~Object(void)
{
	g_object_manager->RemoveObject(this);
}
