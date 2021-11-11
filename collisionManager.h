#pragma once
#include "gameNode.h"
//#include "effect.h"

class player;
class enemyManager;
//class Object;
//class Player_bullet;
//class fragment;
//class Weapon;
//class itemManager;

enum PORTAL
{
	PORTAL_UP, PORTAL_DOWN, PORTAL_LEFT, PORTAL_RIGHT, PORTAL_END
};

class collisionManager
{
private:
	// 맵
	image* _stage;

	player* _player;
	enemyManager* _enemy;

	D2D1_RECT_F temp;

	effect* _hit;

public:
	collisionManager() {};
	~collisionManager() {};

	// 맵 정보를 받아오기 위한 init 함수 
	virtual HRESULT init(image* stage);
	virtual void release();
	virtual void update(int num);
	virtual void render();

	// Link 합시다
	inline void Link_PlayerClass(player* player) { _player = player; }
	inline void Link_EnemyClass(enemyManager* enemy) { _enemy = enemy; }

	// 충돌관리 함수
	void pixel_collision();
	//void pixel_collision_bullet();
	void pixel_collision_enemy();
	//void player_AND_enemy();
	//void player_AND_object();
	//void player_bullet_AND_enemy();
	//void Enemy_bullet_AND_anything();
	//void item_colision();

	//void item_pick_up();
};