#include "stdafx.h"
#include "houseScene.h"

HRESULT houseScene::init()
{
	UIMANAGER->changeUI(CURRENT_UI::HOUSE_SCREEN);

	CAMERAMANAGER->init(1800, 1100);

	_cursor = new mouseCursor;
	_cursor->init();

	_player = new player;
	_player->init(915, 841, PLAYER_DIRECTION :: DOWN);

	_house = IMAGEMANAGER->addImage("houseMap", L"image/house/house.png", 1008 * 2.4, 964 * 2.4);

	_house_pixel = IMAGEMANAGER->addImage("houseMap_pixel", L"image/house/house_pixel.png", 1008, 964);
	_house_pixel->get_RGB(0, 0);

	bookInit();

	// 충돌처리 링크설정
	_collisionManager = new collisionManager;
	_collisionManager->init(_house_pixel);
	_collisionManager->Link_PlayerClass(_player);

	D2DMANAGER->fade(fade_init);

	return S_OK;
}

void houseScene::release()
{
}

void houseScene::update()
{	
	bookUpdate();
	
	if(!_book.isClick) _player->update();
	_cursor->update();

	_collisionManager->update(0);

	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();
	CAMERAMANAGER->updateScreen(_player->getPlayerX(), _player->getPlayerY());
}

void houseScene::render()
{
	_house->render(-300, -600);
	//_house_pixel->render(0, 0);

	_book.img->aniRender(_book.x, _book.y, _book.ani);

	_player->render();

	_book.flash->render(cam_x, cam_y, _book.flash_opacity);

	if (!D2DMANAGER->isFadeOut()) D2DMANAGER->fade(fade_out);

	//텍스트
	WCHAR str2[128];
	swprintf_s(str2, L"x : %f, y : %f", _player->getPlayerX(), _player->getPlayerY());
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"둥근모꼴", 17.0f, str2
									, WINSIZEX / 2 - 200
									, 100
									, WINSIZEX / 2 + 200
									, 200);


	//D2DMANAGER->Rectangle(_book.rc1);
	//D2DMANAGER->Rectangle(_book.rc2);
}

void houseScene::bookInit()
{
	_book.img = IMAGEMANAGER->addFrameImage("book", L"image/house/diary_84x75.png", 669, 75, 8, 1);

	int _book_close[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bookClose", "book", _book_close, 1, 1, true);

	int _book_open[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bookOpen", "book", _book_open, 4, 3, false);

	int _book_loop_1[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop1", "book", _book_loop_1, 4, 4, false);

	int _book_loop_2[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop2", "book", _book_loop_1, 4, 7, false);

	int _book_loop_3[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop3", "book", _book_loop_1, 4, 10, false);

	int _book_loop_4[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop4", "book", _book_loop_1, 4, 12, false);

	int _book_loop_5[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop5", "book", _book_loop_1, 4, 20, false);

	int _book_loop_6[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop6", "book", _book_loop_1, 4, 40, false);

	int _book_loop_7[] = { 7, 6, 5, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bookLoop7", "book", _book_loop_1, 4, 50, true);

	_book.ani = KEYANIMANAGER->findAnimation("bookClose");
	_book.ani->start();

	_book.x = 870;
	_book.y = 650;

	_book.isClick = false;
	_book.isIn = false;

	_book.speedPower = 0.0f;
	_book.flashPower = 0.0f;

	_book.rc1 = D2DMANAGER->RectMake(890, 670, 45, 50);
	_book.rc2 = D2DMANAGER->RectMake(907, 705, 10, 10);

	_book.flash = IMAGEMANAGER->addImage("FLASH", L"image/house/white.png", 1600, 900);
	_book.flash_opacity = 0.0f;
}

void houseScene::bookUpdate()
{
	D2D1_RECT_F rc;
	D2D1_RECT_F player = _player->getTagPlayer().rc;
	D2D1_RECT_F book = _book.rc2;

	_book.isIn = false;

	if (INTERSECTION_RECT(rc, player, book))
	{
		_book.isIn = true;
	}

	if (PTIN_RECT(&_book.rc1, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_book.isIn && !_book.isClick)
			{
				_book.ani = KEYANIMANAGER->findAnimation("bookOpen");
				_book.ani->start();

				_book.isClick = true;
				_player->init(_player->getTagPlayer().x, _player->getTagPlayer().y, PLAYER_DIRECTION::UP);

				MAPMANAGER->init();
			}
		}
	}

	if (KEYANIMANAGER->isEnd("bookOpen") && _book.ani == KEYANIMANAGER->findAnimation("bookOpen"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop1");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop1") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop1"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop2");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop2") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop2"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop3");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop3") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop3"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop4");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop4") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop4"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop5");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop5") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop5"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop6");
		_book.ani->start();
	}
	if (KEYANIMANAGER->isEnd("bookLoop6") && _book.ani == KEYANIMANAGER->findAnimation("bookLoop6"))
	{
		_book.ani = KEYANIMANAGER->findAnimation("bookLoop7");
		_book.ani->start();
	}
	if (_book.isClick)
	{
		if (_book.y > 420)
		{
			_book.speedPower += 0.002f;
			_book.y -= _book.speedPower;
		}

		if (_book.y < 650)
		{
			_book.flashPower += 0.0000115f;
			_book.flash_opacity += _book.flashPower;
		}
	}

	if (_book.y < 421)
	{
		MAPMANAGER->startMap();

		//UIMANAGER->Save(_player);

		SCENEMANAGER->changeScene("시작맵");
	}
}

