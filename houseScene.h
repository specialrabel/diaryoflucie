#pragma once
#include "gameNode.h"
#include "mouseCursor.h"
#include "player.h"
#include "collisionManager.h"
#include "idleState.h"

struct BOOK
{
	image* img;
	animation* ani;
	//rc1�� ĳ���ͷ�Ʈ�� ���ִ��� Ȯ�ο�, rc2�� ���콺Ŀ���� ���ִ��� Ȯ�ο�
	D2D1_RECT_F rc1, rc2;
	bool isIn, isClick;

	float x, y;
	float speedPower;

	image* flash;
	float flash_opacity;
	float flashPower;
};

class houseScene : public gameNode
{
private:
	mouseCursor* _cursor;
	player* _player;
	collisionManager* _collisionManager;

	image* _house;
	image* _house_pixel;

	BOOK _book;

	float cam_x, cam_y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void bookInit();
	void bookUpdate();
};

