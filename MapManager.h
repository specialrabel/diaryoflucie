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

	bool up;		// ���� �� �� �ִ���
	bool down;		// �Ʒ��� �� �� �ִ���
	bool left;		// �������� �� �� �ִ���
	bool right;		// ���������� �� �� �ִ���
	
	bool pass;		// Ŭ���� �� ������ �ƴ���
	bool current;	// �����ִ� ������ �ƴ���
};

class MapManager : public singletonBase<MapManager>
{
private:
	RANDOM_MAP_INFO _random_map[MAP_MAX];

	//���� ����
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