#include "stdafx.h"
#include "startMap.h"

HRESULT startMap::init()
{
	UIMANAGER->changeUI(CURRENT_UI::PLAYING_SCREEN);

	_mapTool = new mapTool;
	_mapTool->init(21, 16);
	_mapTool->load(1);

	_player = new player();
	_player->init(851.59, 687.59, PLAYER_DIRECTION::DOWN);
	UIMANAGER->Save(_player, _mapTool);

	_ui = new ui();
	_ui->init();

	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_UP)		_player->init(838, 1195, PLAYER_DIRECTION::UP);
	else if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_DOWN)	_player->init(850, 83, PLAYER_DIRECTION::DOWN);
	else if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_LEFT)	_player->init(1643, 731, PLAYER_DIRECTION::LEFT);
	else if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_RIGHT)	_player->init(74, 748, PLAYER_DIRECTION::RIGHT);
	else TIMEMANAGER->start_record();

	_start_pixel = IMAGEMANAGER->addImage("startMap_pixel", L"image/startMap/startMap_pixel.png", 1008, 768);
	_start_pixel->get_RGB(0, 0);

	_wall_up = IMAGEMANAGER->addImage("wall_up", L"image/startMap/12시방향.png", 565, 405);
	_wall_down = IMAGEMANAGER->addImage("wall_down", L"image/startMap/6시방향.png", 1048, 322);
	_wall_left = IMAGEMANAGER->addImage("wall_left", L"image/startMap/9시방향.png", 323, 807);
	_wall_right = IMAGEMANAGER->addImage("wall_right", L"image/startMap/3시방향.png", 323, 780);
	
	// 충돌처리 링크설정
	_collisionManager = new collisionManager;
	_collisionManager->init(_start_pixel);
	_collisionManager->Link_PlayerClass(_player);

	_portal[PORTAL_UP].rc = D2DMANAGER->RectMake(700, 0, 300, 30);
	_portal[PORTAL_DOWN].rc = D2DMANAGER->RectMake(620, 1270, 500, 30);
	_portal[PORTAL_LEFT].rc = D2DMANAGER->RectMake(0, 600, 30, 300);
	_portal[PORTAL_RIGHT].rc = D2DMANAGER->RectMake(1670, 590, 30, 300);


	D2DMANAGER->fade(fade_init);
	
	return S_OK;
}

void startMap::release()
{
}

void startMap::update()
{
	UIMANAGER->Load(_player, _mapTool);

	_mapTool->update();

	_collisionManager->update(0);

	startMap_portal();

	CAMERAMANAGER->updateScreen(_player->getPlayerX(), _player->getPlayerY());
	_player->update();
	
	_ui->update();
	
	UIMANAGER->Save(_player, _mapTool);
}

void startMap::render()
{
	_mapTool->render();
	//_start_pixel->render(0, 0);
	//_wall_up_pixel->render(568, 0);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) D2DMANAGER->Rectangle(_portal[PORTAL_UP].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) _wall_up->render(568, 0);


	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) D2DMANAGER->Rectangle(_portal[PORTAL_LEFT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) _wall_left->render(0, 238);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) D2DMANAGER->Rectangle(_portal[PORTAL_RIGHT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) _wall_right->render(1379, 234);

	_player->render();

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) D2DMANAGER->Rectangle(_portal[PORTAL_DOWN].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) _wall_down->render(325, 975);

	_ui->render();

	WCHAR str3[128];
	swprintf_s(str3, L"%d", MAPMANAGER->getCurrentNum());
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"둥근모꼴", 17.0f, str3
		, WINSIZEX / 2 - 600
		, 400
		, WINSIZEX / 2 + 600
		, 600);

	if (!D2DMANAGER->isFadeOut()) D2DMANAGER->fade(fade_out);
	if (!D2DMANAGER->isFadeIn() && D2DMANAGER->isPass()) D2DMANAGER->fade(fade_in);
}

void startMap::startMap_portal()
{
	D2D1_RECT_F rc;
	D2D1_RECT_F player = _player->getTagPlayer().rc;
	D2D1_RECT_F portal_up = _portal[PORTAL_UP].rc;
	D2D1_RECT_F portal_down = _portal[PORTAL_DOWN].rc;
	D2D1_RECT_F portal_left = _portal[PORTAL_LEFT].rc;
	D2D1_RECT_F portal_right = _portal[PORTAL_RIGHT].rc;

	if (INTERSECTION_RECT(rc, player, portal_up) && MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up)
	{
		D2DMANAGER->setIsPass();
		
		if (D2DMANAGER->isFadeIn()) 
		{
			MAPMANAGER->moveMap(MOVE_MAP::MAP_UP);
			SCENEMANAGER->changeScene("맵이동");
		}
	}
	if (INTERSECTION_RECT(rc, player, portal_down) && MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down)
	{
		D2DMANAGER->setIsPass();

		if (D2DMANAGER->isFadeIn())
		{
			MAPMANAGER->moveMap(MOVE_MAP::MAP_DOWN);
			SCENEMANAGER->changeScene("맵이동");
		}
	}
	if (INTERSECTION_RECT(rc, player, portal_left) && MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left)
	{
		D2DMANAGER->setIsPass();

		if (D2DMANAGER->isFadeIn())
		{
			MAPMANAGER->moveMap(MOVE_MAP::MAP_LEFT);
			SCENEMANAGER->changeScene("맵이동");
		}
	}
	if (INTERSECTION_RECT(rc, player, portal_right) && MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right)
	{
		D2DMANAGER->setIsPass();

		if (D2DMANAGER->isFadeIn())
		{
			MAPMANAGER->moveMap(MOVE_MAP::MAP_RIGHT);
			SCENEMANAGER->changeScene("맵이동");
		}
	}
}
