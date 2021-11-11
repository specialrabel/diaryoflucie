#include "stdafx.h"
#include "dungeon.h"

HRESULT dungeon::init()
{
	_mapTool = new mapTool;
	_mapTool->init(23, 20);
	
	_mapTool->load(2);

	_player = new player();
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_UP)		_player->init(932, 1550, PLAYER_DIRECTION::UP);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_DOWN)	_player->init(939, 71, PLAYER_DIRECTION::DOWN);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_LEFT)	_player->init(1803, 864, PLAYER_DIRECTION::LEFT);
	if (MAPMANAGER->getDirection() == MOVE_MAP::MAP_RIGHT)	_player->init(80, 842, PLAYER_DIRECTION::RIGHT);
	UIMANAGER->Save(_player, _mapTool);

	_ui = new ui;
	_ui->init();

	_dungeon_pixel = IMAGEMANAGER->addImage("dungeon_pixel", L"image/dungeon/dungeon_pixel.png", 1877, 1632);
	_dungeon_pixel->get_RGB(0, 0);

	_wall_up = IMAGEMANAGER->addImage("dungeon_up", L"image/dungeon/12시방향.png", 246, 244);
	_wall_down = IMAGEMANAGER->addImage("dungeon_down", L"image/dungeon/6시방향.png", 565, 260);
	_wall_left = IMAGEMANAGER->addImage("dungeon_left", L"image/dungeon/9시방향.png", 161, 808);
	_wall_right = IMAGEMANAGER->addImage("dungeon_right", L"image/dungeon/3시방향.png", 260, 808);

	_enemyManager = new enemyManager;
	_enemyManager->LinkMaptoolClass(_mapTool);
	_enemyManager->LinkPlayerClass(_player);
	_enemyManager->init();

	set_enemy();

	// 충돌처리 링크설정
	_collisionManager = new collisionManager;
	_collisionManager->init(_dungeon_pixel);
	_collisionManager->Link_PlayerClass(_player);
	_collisionManager->Link_EnemyClass(_enemyManager);

	_portal[PORTAL_UP].rc = D2DMANAGER->RectMake(785, 0, 300, 30);
	_portal[PORTAL_DOWN].rc = D2DMANAGER->RectMake(760, 1592, 500, 30);
	_portal[PORTAL_LEFT].rc = D2DMANAGER->RectMake(0, 725, 30, 300);
	_portal[PORTAL_RIGHT].rc = D2DMANAGER->RectMake(1833, 729, 30, 300);

	D2DMANAGER->fade(fade_init);

	return S_OK;
}

void dungeon::release()
{
}

void dungeon::update()
{
	UIMANAGER->Load(_player, _mapTool);

	_mapTool->update();
	_player->update();
	_enemyManager->update();

	_collisionManager->update(1);

	CAMERAMANAGER->updateScreen(_player->getPlayerX(), _player->getPlayerY());

	dungeon1_portal();

	_ui->update();

	UIMANAGER->Save(_player, _mapTool);
	
}

void dungeon::render()
{	
	_mapTool->render();
	//_dungeon_pixel->render(0, 0);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) D2DMANAGER->Rectangle(_portal[PORTAL_UP].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up) _wall_up->render(808, 0);


	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) D2DMANAGER->Rectangle(_portal[PORTAL_LEFT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left) _wall_left->render(0, 326);

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) D2DMANAGER->Rectangle(_portal[PORTAL_RIGHT].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right) _wall_right->render(1618, 324);

	_player->render();
	_enemyManager->render();

	//if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) D2DMANAGER->Rectangle(_portal[PORTAL_DOWN].rc);
	if (!MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down) _wall_down->render(648, 1378);

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

void dungeon::dungeon1_portal()
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

void dungeon::set_enemy()
{
	_enemyManager->set_maggots(978, 787);

	//_enemyManager->set_maggots(700, 300);
	//
	//_enemyManager->set_maggots(1200, 550);
	//
	//_enemyManager->set_maggots(400, 600);
	//
	//_enemyManager->set_maggots(900, 500);
	//
	//_enemyManager->set_maggots(800, 850);
}
