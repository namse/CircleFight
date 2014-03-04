#pragma once
#include "event_listener.h"
enum Shape
{
	CIRCLE,
	POLYGON,
};
class Object
	: public EventListener
{
public:
	Object();
	virtual ~Object(void);

	
	void Update(float d_time);
	
	ObjectID GetObjectID(){ return object_id_; }

protected:
	


	ObjectID object_id_;

	int hp_;
	bool has_hp_;

	int mp_;
	bool has_mp_;

	Point position_;
	Point velocity_;

	Shape shape_;

	bool is_collidable;

private:
	
	void SetObjectID( ObjectID object_id){ object_id_ = object_id; }
	
	friend class ObjectManager;
};



