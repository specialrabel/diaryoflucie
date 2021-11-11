#pragma once


class player;

class STATE
{
private:
	player* _player;

public:

	virtual STATE* inputHandle(player* player) = 0;
	virtual void update(player* player) = 0;
	virtual void enter(player* player) = 0;
	virtual void exit(player* player) = 0;
};
