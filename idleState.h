#pragma once
#include "State.h"

class player;

class IdleState :
	public STATE
{
public:
	virtual STATE* inputHandle(player* player);
	virtual void update(player* player);
	virtual void enter(player* player);
	virtual void exit(player* player);
};

