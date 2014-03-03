#pragma once
#include "object.h"
class Skill :
	public Object
{
public:
	Skill(void);
	virtual ~Skill(void);

		
	void Update(float d_time);
};

