#include "stdafx.h"
#include "maggot.h"

HRESULT maggot::init(float x, float y)
{
	IMAGEMANAGER->addFrameImage("slime", L"image/enemy/slime.png", 240, 1040, 3, 13);

	animation_init();
	enemy_img = IMAGEMANAGER->findImage("slime");
	enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
	enemy_body->start();

	_rc = D2DMANAGER->RectMakeCenter(x, y,
		60, 60);

	max_hp = hp = 20;

	_x = x;
	_y = y;
	_width = _rc.right - _rc.left;
	_height = _rc.bottom - _rc.top;

	_speed = 2.0f;
	_angle = 0.0f;

	_state = enemy_state::IDLE;
	_direction = enemy_direction::RIGHT;
	_kind = enemy_kind::MAGGOT;

	maggot_bullet = new Player_bullet;
	maggot_bullet->init(800);

	_elapsedSec = 0;
	_frameUpdateSec = 1.0f / 60;

	_index = 0;
	count = 0;
	idle_count = 0;
	acition_count = 0;
	action_count = 0;

	is_find = false;
	is_arrived = false;
	is_done = false;

	return S_OK;
}

void maggot::release()
{
}

void maggot::update()
{
	action_count++;

	if(_state != enemy_state::ATTACK) update_direction();
	
	state_action();
	
	if (past_direction != _direction)
	{
		animation_setting();
	}

	if (is_find && _state == enemy_state::IDLE || is_find && _state == enemy_state::IDLE_RUN)
	{
		animation_setting();
		_state = enemy_state::RUN;
	}
	else if (!is_find && _state == enemy_state::RUN)
	{
		animation_setting();
		_state = enemy_state::IDLE;
	}
	
	past_direction = _direction;

	maggot_bullet->update();

}

void maggot::render()
{
	enemy_img->aniRender(_rc.left - 10, _rc.top - 20, enemy_body);

	maggot_bullet->render();
	D2DMANAGER->Rectangle(_rc);
}

void maggot::idle()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	if (idle_count > 1.0f)
	{
		_angle = RND->getFromFloatTo(-PI * 2, PI * 2);
		update_direction();
		_state = enemy_state::IDLE_RUN;
		animation_setting();
		idle_count = 0;
	}
}

void maggot::idle_run()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	_rc.left += _speed * 0.5 * cosf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.right = _rc.left + _width;

	_rc.top += _speed * 0.5 * -sinf(_angle)* TIMEMANAGER->getElapsedTime() * 60;
	_rc.bottom = _rc.top + _height;

	if (idle_count > 1.5f)
	{
		_state = enemy_state::IDLE;
		animation_setting();
		idle_count = 0;
	}
}

void maggot::move()
{
	idle_count += TIMEMANAGER->getElapsedTime();

	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	if (_list.size() > 0) {
		D2D1_RECT_F temp = _list[_index];


		float dest_x = (temp.left + temp.right) / 2;
		float dest_y = (temp.top + temp.bottom) / 2;

		float distance = getDistance(enemy_x, enemy_y, dest_x, dest_y);
		float distance2 = getDistance(enemy_x, enemy_y, (_destination.left + _destination.right) / 2, (_destination.top + _destination.bottom) / 2);
		float angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

		_angle = angle;

		if (distance > 3 && !is_arrived)
		{
			_rc.left += _speed * cosf(angle)* TIMEMANAGER->getElapsedTime() * 60;
			_rc.right = _rc.left + _width;

			_rc.top += RND->getFromFloatTo(0.0f, 2.0f) * -sinf(angle)* TIMEMANAGER->getElapsedTime() * 60;
			_rc.bottom = _rc.top + _height;
		}
		else
		{
			is_done = true;
		}

		if (is_done)
		{
			_index -= 1;
			is_done = false;
		}

		if (_index < 0)
		{
			_index = 0;
			is_arrived = true;
		}

		if (distance2 < 180)
		{
			is_arrived = true;

			_state = enemy_state::ATTACK;
			//animation_setting();
			is_fire = true;
		}
	}
}

void maggot::attack()
{
	acition_count += TIMEMANAGER->getElapsedTime();

	float enemy_x = (_rc.left + _rc.right) / 2;
	float enemy_y = (_rc.top + _rc.bottom) / 2;

	float dest_x = (_destination.left + _destination.right) / 2;
	float dest_y = (_destination.top + _destination.bottom) / 2;

	_angle = getAngle(enemy_x, enemy_y, dest_x, dest_y);

	if (is_fire)
	{
		animation_setting();

		maggot_bullet->fire(L"image/bullet/slime_bullet.png", enemy_x, enemy_y, 112, 112, _angle, 4.0f);
		maggot_bullet->fire(L"image/bullet/slime_bullet.png", enemy_x, enemy_y, 112, 112, _angle + 0.4f, 4.0f);
		maggot_bullet->fire(L"image/bullet/slime_bullet.png", enemy_x, enemy_y, 112, 112, _angle - 0.4f, 4.0f);

		is_fire = false;
	}

	if (acition_count > 1.8f)
	{
		acition_count = 0;
		idle_count = 0;
		_index = 0;
		_state = enemy_state::IDLE;
		state_action();
		animation_setting();

		is_arrived = false;
	}
}

void maggot::state_action()
{
	switch (_state)
	{
	case enemy_state::IDLE:
		idle();
		break;
	case enemy_state::IDLE_RUN:
		idle_run();
		break;
	case enemy_state::RUN:
		move();
		break;
	case enemy_state::ATTACK:
		attack();
		break;
	}
}

void maggot::update_direction()
{
	if (_angle >= PI2) _angle -= PI2;
	if (_angle <= 0) _angle += PI2;

	if (_angle > 0 && _angle <= PI8)
	{
		_direction = enemy_direction::RIGHT;
		_angle = 0.0f;
	}
	else if (_angle > PI8 && _angle <= 3 * PI8)
	{
		_direction = enemy_direction::RIGHT_TOP;
	}
	else if (_angle > 3 * PI8 && _angle <= 5 * PI8)
	{
		_direction = enemy_direction::TOP;
		_angle = PI / 2;
	}
	else if (_angle > 5 * PI8 && _angle <= 7 * PI8)
	{
		_direction = enemy_direction::LEFT_TOP;
	}
	else if (_angle > 7 * PI8 && _angle <= 9 * PI8)
	{
		_direction = enemy_direction::LEFT;
		_angle = PI;
	}
	else if (_angle > 9 * PI8 && _angle <= 11 * PI8)
	{
		_direction = enemy_direction::LEFT_BOTTOM;
	}
	else if (_angle > 11 * PI8 && _angle <= 13 * PI8)
	{
		_direction = enemy_direction::BOTTOM;
		_angle = PI + PI / 2;
	}
	else if (_angle > 13 * PI8 && _angle <= 15 * PI8)
	{
		_direction = enemy_direction::RIGHT_BOTTOM;
	}
	else
	{
		_direction = enemy_direction::RIGHT;
	}
}

void maggot::animation_init()
{
	int left_idle[] = { 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_idle_maggot", "slime", left_idle, 3, 4.0, true);
	int left_run[] = { 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_run_maggot", "slime", left_run, 3, 4.0, true);
	int left_attack[] = { 3, 15, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("left_attack_maggot", "slime", left_attack, 3, 10, false);

	int left_top_idle[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_idle_maggot", "slime", left_top_idle, 3, 4.0, true);
	int left_top_run[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_run_maggot", "slime", left_top_run, 3, 4.0, true);
	int left_top_attack[] = { 9, 21, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("left_top_attack_maggot", "slime", left_top_attack, 3, 10, false);

	int top_idle[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("top_idle_maggot", "slime", top_idle, 3, 4.0, true);
	int top_run[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("top_run_maggot", "slime", top_run, 3, 4.0, true);
	int top_attack[] = { 9, 21, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("top_attack_maggot", "slime", top_attack, 3, 10, false);

	int right_top_idle[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_idle_maggot", "slime", right_top_idle, 3, 4.0, true);
	int right_top_run[] = { 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_run_maggot", "slime", right_top_run, 3, 4.0, true);
	int right_top_attack[] = { 9, 21, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("right_top_attack_maggot", "slime", right_top_attack, 3, 10, false);

	int right_idle[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("right_idle_maggot", "slime", right_idle, 3, 4.0, true);
	int right_run[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("right_run_maggot", "slime", right_run, 3, 4.0, true);
	int right_attack[] = { 6, 18, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("right_attack_maggot", "slime", right_attack, 3, 10, false);

	int left_bottom_idle[] = { 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_idle_maggot", "slime", left_bottom_idle, 3, 4.0, true);
	int left_bottom_run[] = { 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_run_maggot", "slime", left_bottom_run, 3, 4.0, true);
	int left_bottom_attack[] = { 3, 15, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("left_bottom_attack_maggot", "slime", left_bottom_attack, 3, 10, false);

	int bottom_idle[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_idle_maggot", "slime", bottom_idle, 3, 4.0, true);
	int bottom_run[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_run_maggot", "slime", bottom_run, 3, 4.0, true);
	int bottom_attack[] = { 0, 12, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("bottom_attack_maggot", "slime", bottom_attack, 3, 10, false);

	int right_bottom_idle[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_idle_maggot", "slime", right_bottom_idle, 3, 4.0, true);
	int right_bottom_run[] = { 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_run_maggot", "slime", right_bottom_run, 3, 4.0, true);
	int right_bottom_attack[] = { 6, 18, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("right_bottom_attack_maggot", "slime", right_bottom_attack, 3, 10, false);

}

void maggot::animation_setting()
{
	switch (_direction)
	{
	case enemy_direction::LEFT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_attack_maggot");
			enemy_body->start();
	
		}
		break;
	case enemy_direction::TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("top_attack_maggot");
			enemy_body->start();
	
		}
		break;
	
	case enemy_direction::RIGHT:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_attack_maggot");
			enemy_body->start();
		}
		break;
	
	case enemy_direction::BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("bottom_attack_maggot");
			enemy_body->start();
		}
		break;
	
	case enemy_direction::LEFT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_top_attack_maggot");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_TOP:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_top_attack_maggot");
			enemy_body->start();
		}
		break;
	
	case enemy_direction::LEFT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("left_bottom_attack_maggot");
			enemy_body->start();
		}
		break;
	case enemy_direction::RIGHT_BOTTOM:
		if (_state == enemy_state::IDLE)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_idle_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::IDLE_RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::RUN)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_run_maggot");
			enemy_body->start();
		}
		if (_state == enemy_state::ATTACK)
		{
			enemy_body = KEYANIMANAGER->findAnimation("right_bottom_attack_maggot");
			enemy_body->start();
		}
	}
}
