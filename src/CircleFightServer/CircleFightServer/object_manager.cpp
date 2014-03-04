#include "object_manager.h"
#include "config.h"

ObjectManager::ObjectManager(void)
{
}


ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::Update(float d_time)
{
	for ( auto it = objects_.begin(); it != objects_.end(); it++)
	{
		it->second->Update(d_time);
	}
}
void ObjectManager::AddObject(Object* object)
{
	object->object_id_ = GenerateObjectID();
	objects_[object->object_id_] = object;

}
Object* ObjectManager::GetObject(ObjectID object_id)
{
	return objects_[object_id];
}
void ObjectManager::RemoveObject(ObjectID object_id)
{
	objects_.erase(object_id);
}
void ObjectManager::RemoveObject(Object* object)
{
	objects_.erase(object->object_id_);
}

ObjectID ObjectManager::GenerateObjectID()
{
	for(int i=0; i<MAX_OBJECT; i++)
	{
		if( objects_.find( (ObjectID)i ) == objects_.end() )
		{
			return i;
		}
	}
}


ObjectManager* g_object_manager = nullptr;