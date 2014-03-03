#include "object_manager.h"


ObjectManager::ObjectManager(void)
{
}


ObjectManager::~ObjectManager(void)
{
}

void ObjectManager::Update(float d_time)
{

}
ObjectID ObjectManager::AddObject(Object* object)
{
	return NULL;
}
Object* ObjectManager::GetObject(ObjectID object_id)
{
	
	return nullptr;
}
void ObjectManager::RemoveObject(ObjectID object_id)
{

}
void ObjectManager::RemoveObject(Object* object)
{

}


ObjectManager* g_object_manager = nullptr;