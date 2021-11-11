#pragma once
#include "gameNode.h"
#include "mouseCursor.h"
#include "player.h"
#include "collisionManager.h"
#include "mapTool.h"
#include "ui.h"
#include "enemyManager.h"

struct DUNGEON1_PORTAL
{
	D2D1_RECT_F rc;
	float x, y;
	float width, height;
};

class dungeon : public gameNode
{
private:
	mouseCursor* _cursor;
	player* _player;
	ui* _ui;
	collisionManager* _collisionManager;
	enemyManager* _enemyManager;

	mapTool* _mapTool;

	DUNGEON1_PORTAL _portal[PORTAL_END];

	image* _dungeon_pixel;

	image* _wall_up;
	image* _wall_down;
	image* _wall_left;
	image* _wall_right;

	float cam_x, cam_y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void dungeon1_portal();

	void set_enemy();
};