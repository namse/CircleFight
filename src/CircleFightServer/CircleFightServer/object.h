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
	
	ObjectID object_id_;
protected:

	int hp_;
	bool has_hp_;

	int mp_;
	bool has_mp_;

	Point position_;
	Point velocity_;

	Shape shape_;

	bool is_collidable;


};


