#pragma once
#include "object.h"
enum State
{
	IDLE,
	MOVE,
};
class Player :
	public Object
{
public:
	Player();
	virtual ~Player(void);
	
	void Update(float d_time);
	
	virtual void Notify(EventHeader& event);

	void TransState(const State to_state);
	bool CouldTransState(const State to_state);

private:
	State state_;
};

