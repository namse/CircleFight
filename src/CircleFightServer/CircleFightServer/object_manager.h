#pragma once
#include "object.h"

#include <map>

class ObjectManager
{
public:
	ObjectManager(void);
	~ObjectManager(void);

	void Update(float d_time);
	void AddObject(Object* object);
	Object* GetObject(ObjectID object_id);
	
	void RemoveObject(ObjectID object_id);
	void RemoveObject(Object* object);
private:

	ObjectID GenerateObjectID();

	std::map<ObjectID,Object*> objects_;
};


extern ObjectManager* g_object_manager;