#pragma once
#include "gameNode.h"
#include "title.h"
#include "mapTool.h"
#include "mapChange.h"
#include "houseScene.h"
#include "startMap.h"
#include "dungeon.h"
#include "dungeon2.h"

#include "player.h"
#include "mouseCursor.h"

struct CameraTarget
{
	float x, y;
	float speed;
};

class playGround : public gameNode
{
private:
	
	title* _title;
	mapTool* _mapTool;
	mapChange* _mapChange;
	houseScene* _house;
	startMap* _startMap;
	dungeon* _dungeon;
	dungeon2* _dungeon2;

	mouseCursor* _mouseCursor;

	bool _isStart;
	int _time;


public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

