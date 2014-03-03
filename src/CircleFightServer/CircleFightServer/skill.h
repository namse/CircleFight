#pragma once
#include "object.h"
class Skill :
	public Object
{
public:
	Skill();
	virtual ~Skill(void);

		
	void Update(float d_time);
};

