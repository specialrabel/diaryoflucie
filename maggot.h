#pragma once
#include "enemy.h"

enum maggot_previousState
{
	idle,
	idle_run,
	run,
	attack
};

class maggot : public enemy
{
private:
	bool is_done;
	float count;
	float idle_count;
	float acition_count;
	float action_count;

	bool is_fire;

	enemy_direction past_direction;

public:

	virtual HRESULT init(float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void idle();
	virtual void idle_run();
	virtual void move();
	virtual void attack();

	virtual void state_action();
	virtual void update_direction();

	void animation_init();
	void animation_setting();
};

