#pragma once
#include "stdafx.h"
#include "singletonBase.h"

#define MAP_MAX 16

enum MOVE_MAP
{
	MAP_START,
	MAP_UP,
	MAP_DOWN,
	MAP_LEFT,
	MAP_RIGHT
};

enum RANDOM_MAP
{
	START_MAP,
	DUNGEON1_MAP,
	DUNGEON2_MAP,
	END_MAP
};

struct RANDOM_MAP_INFO
{
	int type;

	bool up;		// 위로 갈 수 있는지
	bool down;		// 아래로 갈 수 있는지
	bool left;		// 왼쪽으로 갈 수 있는지
	bool right;		// 오른쪽으로 갈 수 있는지
	
	bool pass;		// 클리어 한 방인지 아닌지
	bool current;	// 현재있는 방인지 아닌지
};

class MapManager : public singletonBase<MapManager>
{
private:
	RANDOM_MAP_INFO _random_map[MAP_MAX];

	//들어온 방향
	int _direction;

public:
	HRESULT init();
	void release();

	void randomMap();
	void startMap();
	void moveMap(int dir);

	int getCurrentNum();

	int getRandomMap(int num) { return _random_map[num].type; }
	int getDirection() { return _direction; }
	RANDOM_MAP_INFO getTagMapInfo(int num) { return _random_map[num]; }
};