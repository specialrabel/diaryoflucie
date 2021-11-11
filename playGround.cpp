#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_title = new title;
	_mapTool = new mapTool;
	_mapChange = new mapChange;
	_house = new houseScene;
	_startMap = new startMap;
	_dungeon = new dungeon;
	_dungeon2 = new dungeon2;

	_mouseCursor = new mouseCursor;
	_mouseCursor->init();

	SCENEMANAGER->addScene("타이틀", _title);
	SCENEMANAGER->addScene("맵툴", _mapTool);
	SCENEMANAGER->addScene("맵이동", _mapChange);
	SCENEMANAGER->addScene("집", _house);
	SCENEMANAGER->addScene("시작맵", _startMap);
	SCENEMANAGER->addScene("던전", _dungeon);
	SCENEMANAGER->addScene("던전2", _dungeon2);
	SCENEMANAGER->changeScene("타이틀");

	_time = 0;

	ShowCursor(false);

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

void playGround::update()
{
	gameNode::update();

	++_time;

	
	if (_time > 20) _isStart = true;

	if (_isStart) SCENEMANAGER->update();
	
	_mouseCursor->update();

	KEYANIMANAGER->update();
}

void playGround::render()
{
	D2DMANAGER->BeginDraw();

	if (_isStart)
	{
		SCENEMANAGER->render();
		_mouseCursor->render();
		//TIMEMANAGER->render();
	}

	D2DMANAGER->EndDraw();
}
