#pragma once
#include "object.h"
class Bullet :
	public Object
{
public:
	Bullet();
	virtual ~Bullet(void);

	
	void Update(float d_time);
};

