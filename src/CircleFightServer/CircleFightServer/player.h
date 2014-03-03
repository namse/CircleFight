#pragma once
#include "object.h"
class Player :
	public Object
{
public:
	Player(void);
	virtual ~Player(void);

	
	void Update(float d_time);
};

