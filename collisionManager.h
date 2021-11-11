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
	// ��
	image* _stage;

	player* _player;
	enemyManager* _enemy;

	D2D1_RECT_F temp;

	effect* _hit;

public:
	collisionManager() {};
	~collisionManager() {};

	// �� ������ �޾ƿ��� ���� init �Լ� 
	virtual HRESULT init(image* stage);
	virtual void release();
	virtual void update(int num);
	virtual void render();

	// Link �սô�
	inline void Link_PlayerClass(player* player) { _player = player; }
	inline void Link_EnemyClass(enemyManager* enemy) { _enemy = enemy; }

	// �浹���� �Լ�
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