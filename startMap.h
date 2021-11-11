#pragma once
#include "gameNode.h"
#include "mouseCursor.h"
#include "player.h"
#include "collisionManager.h"
#include "mapTool.h"
#include "ui.h"

struct STARTMAP_PORTAL
{
	D2D1_RECT_F rc;
	float x, y;
	float width, height;
};

class startMap : public gameNode
{
private:
	mouseCursor* _cursor;
	player* _player;
	ui* _ui;
	collisionManager* _collisionManager;

	mapTool* _mapTool;

	STARTMAP_PORTAL  _portal[PORTAL_END];

	image* _start_pixel;
	
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

	void startMap_portal();
};