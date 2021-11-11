#include "stdafx.h"
#include "dungeon2.h"

HRESULT dungeon2::init()
{
	_mapTool = new mapTool;
	_mapTool->init(21, 14);

	_mapTool->load(3);

	_player = new player();
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_UP)		_player->init(864, 1054, PLAYER_DIRECTION::UP);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_DOWN)	_player->init(853, 77, PLAYER_DIRECTION::DOWN);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_LEFT)	_player->init(1631, 717, PLAYER_DIRECTION::LEFT);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_RIGHT)	_player->init(58, 722, PLAYER_DIRECTION::RIGHT);
	UIMANAGER->Load(_player, _mapTool);

	_ui = new ui();
	_ui->init();

	_dungeon2_pixel = IMAGEMANAGER->addImage("dungeon2_pixel", L"image/dungeon2/dungeon2_pixel.png", 1714, 1142);
	_dungeon2_pixel->get_RGB(0, 0);

	_wall_up = IMAGEMANAGER->addImage("dungeon2_up", L"image/dungeon2/12시방향.png", 246, 244);
	_wall_down = IMAGEMANAGER->addImage("dungeon2_down", L"image/dungeon2/6시방향.png", 403, 86);
	_wall_left = IMAGEMANAGER->addImage("dungeon2_left", L"image/dungeon2/9시방향.png", 323, 808);
	_wall_right = IMAGEMANAGER->addImage("dungeon2_right", L"image/dungeon2/3시방향.png", 246, 808);

	// 충돌처리 링크설정
	_collisionManager = new collisionManager;
	_collisionManager->init(_dungeon2_pixel);
	_collisionManager->Link_PlayerClass(_player);

	_portal[PORTAL_UP].rc = D2DMANAGER->RectMake(699, 0, 300, 30);
	_portal[PORTAL_DOWN].rc = D2DMANAGER->RectMake(705, 1103, 500, 30);
	_portal[PORTAL_LEFT].rc = D2DMANAGER->RectMake(0, 573, 30, 300);
	_portal[PORTAL_RIGHT].rc = D2DMANAGER->RectMake(1670, 591, 30, 300);

	D2DMANAGER->fade(fade_init);

	return S_OK;
}

void dungeon2::release()
{
}

void dungeon2::update()
{
	UIMANAGER->Load(_player, _mapTool);

	_player->update();
	_mapTool->update();

	_collisionManager->update(0);

	CAMERAMANAGER->updateScreen(_player->getPlayerX(), _player->getPlayerY());

	dungeon2_portal();

	_ui->update();

	UIMANAGER->Save(_player, _mapTool);
}

void dungeon2::render()
{
	_mapTool->render();
	//_dungeon2_pixel->render(0, 0);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) D2DMANAGER->Rectangle(_portal[PORTAL_UP].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) _wall_up->render(728, 0);


	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) D2DMANAGER->Rectangle(_portal[PORTAL_LEFT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) _wall_left->render(0, 246);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) D2DMANAGER->Rectangle(_portal[PORTAL_RIGHT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) _wall_right->render(1458, 244);

	_player->render();

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) D2DMANAGER->Rectangle(_portal[PORTAL_DOWN].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) _wall_down->render(648, 1052);

	WCHAR str3[128];
	swprintf_s(str3, L"%d", MAPMANAGER->getCurrentNum());
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"둥근모꼴", 17.0f, str3
		, WINSIZEX / 2 - 600
		, 400
		, WINSIZEX / 2 + 600
		, 600);

	_ui->render();

	if (!D2DMANAGER->isFadeOut()) D2DMANAGER->fade(fade_out);
	if (!D2DMANAGER->isFadeIn() && D2DMANAGER->isPass()) D2DMANAGER->fade(fade_in);
}

void dungeon2::dungeon2_portal()
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