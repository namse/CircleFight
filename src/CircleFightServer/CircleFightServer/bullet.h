#pragma once
#include "object.h"
class Bullet :
	public Object
{
public:
	Bullet(void);
	virtual ~Bullet(void);

	
	void Update(float d_time);
};

