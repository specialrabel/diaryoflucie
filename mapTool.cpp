#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	_player = new player;
	_player->cameraInit(1600, 900, 10.0f);

	_cursor = new mouseCursor;
	_cursor->init();
	
	_mapTile = IMAGEMANAGER->addFrameImage("MapTiles1", L"image/mapTool/maptiles1.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile2 = IMAGEMANAGER->addFrameImage("MapTiles2", L"image/mapTool/maptiles2.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile3 = IMAGEMANAGER->addFrameImage("MapTiles3", L"image/mapTool/maptiles3.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile4 = IMAGEMANAGER->addFrameImage("MapTiles4", L"image/mapTool/maptiles4.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile5 = IMAGEMANAGER->addFrameImage("MapTiles5", L"image/mapTool/maptiles5.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);

	_sampleMapTile = IMAGEMANAGER->addFrameImage("sampleMapTiles1", L"image/mapTool/maptiles1.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile2 = IMAGEMANAGER->addFrameImage("sampleMapTiles2", L"image/mapTool/mapTiles2.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile3 = IMAGEMANAGER->addFrameImage("sampleMapTiles3", L"image/mapTool/mapTiles3.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile4 = IMAGEMANAGER->addFrameImage("sampleMapTiles4", L"image/mapTool/mapTiles4.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile5 = IMAGEMANAGER->addFrameImage("sampleMapTiles5", L"image/mapTool/mapTiles5.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);

	_pageButton[PAGE1].img = IMAGEMANAGER->addImage("PAGE1_BUTTON", L"image/mapTool/PAGE1_BUTTON.png", 98, 63);
	_pageButton[PAGE2].img = IMAGEMANAGER->addImage("PAGE2_BUTTON", L"image/mapTool/PAGE2_BUTTON.png", 98, 63);
	_pageButton[PAGE3].img = IMAGEMANAGER->addImage("PAGE3_BUTTON", L"image/mapTool/PAGE3_BUTTON.png", 98, 63);
	_pageButton[PAGE4].img = IMAGEMANAGER->addImage("PAGE4_BUTTON", L"image/mapTool/PAGE4_BUTTON.png", 98, 63);
	_pageButton[PAGE5].img = IMAGEMANAGER->addImage("PAGE5_BUTTON", L"image/mapTool/PAGE5_BUTTON.png", 98, 63);

	_attributeButton[TR_BTN].img = IMAGEMANAGER->addImage("TR_BTN", L"image/mapTool/TERRAIN_BUTTON.png", 109, 32);
	IMAGEMANAGER->addImage("TR_BTN_PUSH", L"image/mapTool/TERRAIN_BUTTON_PUSH.png", 109, 32);

	_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->addImage("OBJ1_BTN", L"image/mapTool/OBJ1_BUTTON.png", 126, 32);
	IMAGEMANAGER->addImage("OBJ1_BTN_PUSH", L"image/mapTool/OBJ1_BUTTON_PUSH.png", 126, 32);

	_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->addImage("OBJ2_BTN", L"image/mapTool/OBJ2_BUTTON.png", 112, 32);
	IMAGEMANAGER->addImage("OBJ2_BTN_PUSH", L"image/mapTool/OBJ2_BUTTON_PUSH.png", 112, 32);

	_attributeButton[COLLISION_BTN].img = IMAGEMANAGER->addImage("COLLISION_BTN", L"image/mapTool/COLLISION_BUTTON.png", 126, 32);
	IMAGEMANAGER->addImage("COLLISION_BTN_PUSH", L"image/mapTool/COLLISION_BUTTON_PUSH.png", 126, 32);

	_attributeButton[ERASE_BTN].img = IMAGEMANAGER->addImage("ERASE_BTN", L"image/mapTool/ERASE_BUTTON.png", 112, 32);
	IMAGEMANAGER->addImage("ERASE_BTN_PUSH", L"image/mapTool/ERASE_BUTTON_PUSH.png", 112, 32);

	_saveButton.img = IMAGEMANAGER->addImage("SAVE_BTN", L"image/mapTool/SAVE_BUTTON.png", 96, 31);
	IMAGEMANAGER->addImage("SAVE_BTN_PUSH", L"image/mapTool/SAVE_BUTTON_PUSH.png", 96, 31);

	_loadButton.img = IMAGEMANAGER->addImage("LOAD_BTN", L"image/mapTool/LOAD_BUTTON.png", 96, 31);
	IMAGEMANAGER->addImage("LOAD_BTN_PUSH", L"image/mapTool/LOAD_BUTTON_PUSH.png", 96, 31);

	IMAGEMANAGER->addImage("textBoxX", L"image/mapTool/textBoxX.png", 51, 32);
	IMAGEMANAGER->addImage("textBoxY", L"image/mapTool/textBoxY.png", 51, 32);
	IMAGEMANAGER->addImage("textBox2", L"image/mapTool/textBox1_push.png", 51, 32);

	_textBox[0].img = IMAGEMANAGER->findImage("textBoxX");
	_textBox[1].img = IMAGEMANAGER->findImage("textBoxY");

	_tileUI.img = IMAGEMANAGER->addImage("mapTool_window", L"image/mapTool/mapWindow.png", 397, 660);
	_tileUI.bar_img = IMAGEMANAGER->addImage("mapTool_bar", L"image/mapTool/mapWindowBar.png", 397, 35);

	_tileUI.x = 1090;
	_tileUI.y = 110;

	_exitButton.img = IMAGEMANAGER->addImage("EXIT_BTN_1", L"image/mapTool/EXIT_BUTTON_1.png", 178, 46);
	IMAGEMANAGER->addImage("EXIT_BTN_2", L"image/mapTool/EXIT_BUTTON_2.png", 178, 46);
	IMAGEMANAGER->addImage("EXIT_BTN_3", L"image/mapTool/EXIT_BUTTON_3.png", 178, 46);

	setup();

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	if (SCENEMANAGER->currentScene("맵툴"))
	{

		_player->update();
		_cursor->update();

		CAMERAMANAGER->updateScreen(_player->getPlayerX(), _player->getPlayerY());

		cam_x = CAMERAMANAGER->get_camera_x();
		cam_y = CAMERAMANAGER->get_camera_y();

		if (_ptMouse2.x > 1590) _player->setPlayerX(8.0f);
		if (_ptMouse2.x < 10) _player->setPlayerX(-8.0f);
		if (_ptMouse2.y > 890) _player->setPlayerY(8.0f);
		if (_ptMouse2.y < 10) _player->setPlayerY(-8.0f);

		ui_update();

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			setMap();
		}
	}

	//타일셋 세팅
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//타일셋에 렉트를 씌움
			_sampleTile[i * SAMPLETILEX + j].rcTile = D2DMANAGER->RectMake(
				(_tileUI.rc.left + 124) + j * _sampleMapTile->getFrameWidth(),
				(_tileUI.rc.top + 51) + i * _sampleMapTile->getFrameHeight(),
				_sampleMapTile->getFrameWidth(),
				_sampleMapTile->getFrameHeight());
		}
	}
}

void mapTool::render()
{
	//지형 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		if (_tiles[i].trPage == PAGE1_TR)
		{
			_mapTile->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}

		if (_tiles[i].trPage == PAGE2_TR)
		{
			_mapTile2->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}

		if (_tiles[i].trPage == PAGE3_TR)
		{
			_mapTile3->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}

		if (_tiles[i].trPage == PAGE4_TR)
		{
			_mapTile4->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}

		if (_tiles[i].trPage == PAGE5_TR)
		{
			_mapTile5->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		}
	}
	
	//오브젝트1 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//오브젝트 속성이 아니면 그리지않게끔 예외처리
		if (_tiles[i].obj == OBJ_NONE) continue;
	
		if (_tiles[i].objPage1 == PAGE1_OBJ1)
		{
			_mapTile->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj1FrameX, _tiles[i].obj1FrameY);
		}

		if (_tiles[i].objPage1 == PAGE2_OBJ1)
		{
			_mapTile2->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj1FrameX, _tiles[i].obj1FrameY);
		}

		if (_tiles[i].objPage1 == PAGE3_OBJ1)
		{
			_mapTile3->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj1FrameX, _tiles[i].obj1FrameY);
		}

		if (_tiles[i].objPage1 == PAGE4_OBJ1)
		{
			_mapTile4->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj1FrameX, _tiles[i].obj1FrameY);
		}

		if (_tiles[i].objPage1 == PAGE5_OBJ1)
		{
			_mapTile5->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj1FrameX, _tiles[i].obj1FrameY);
		}
	}

	//오브젝트2 그리기
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		//오브젝트 속성이 아니면 그리지않게끔 예외처리
		if (_tiles[i].obj == OBJ_NONE) continue;

		if (_tiles[i].objPage2 == PAGE1_OBJ2)
		{
			_mapTile->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj2FrameX, _tiles[i].obj2FrameY);
		}

		if (_tiles[i].objPage2 == PAGE2_OBJ2)
		{
			_mapTile2->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj2FrameX, _tiles[i].obj2FrameY);
		}

		if (_tiles[i].objPage2 == PAGE3_OBJ2)
		{
			_mapTile3->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj2FrameX, _tiles[i].obj2FrameY);
		}

		if (_tiles[i].objPage2 == PAGE4_OBJ2)
		{
			_mapTile4->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj2FrameX, _tiles[i].obj2FrameY);
		}

		if (_tiles[i].objPage2 == PAGE5_OBJ2)
		{
			_mapTile5->FrameRender(
				_tiles[i].rc.left, _tiles[i].rc.top,
				_tiles[i].obj2FrameX, _tiles[i].obj2FrameY);
		}
	}

	if (SCENEMANAGER->currentScene("맵툴"))
	{

		//속성별 렉트표시
		for (int i = 0; i < TILEX*TILEY; i++) {
			if (_tiles[i].obj == OBJ_WALL)D2DMANAGER->Rectangle_brush(D2DMANAGER->CreateBrush(0xFF0000), _tiles[i].rc);
		}

		ui_render();
	}

}

//맵툴 틀 셋업
void mapTool::setup()
{
	_ctrSelect = CTRL_TERRAINDRAW;

	_currentTile.x = 5;
	_currentTile.y = 5;

	_tileUI.rc = D2DMANAGER->RectMake(_tileUI.x, _tileUI.y, _tileUI.img->getWidth(), _tileUI.img->getHeight());

	//타일셋 먼저 세팅
	for (int i = 0; i < SAMPLETILEY; ++i)
	{
		for (int j = 0; j < SAMPLETILEX; ++j)
		{
			_sampleTile[i * SAMPLETILEX + j].terrainFrameX = j;
			_sampleTile[i * SAMPLETILEX + j].terrainFrameY = i;

			//타일셋에 렉트를 씌움
			_sampleTile[i * SAMPLETILEX + j].rcTile = D2DMANAGER->RectMake(
				(_tileUI.rc.left + 124) + j * _mapTile->getFrameWidth(),
				(_tileUI.rc.top + 51) + i * _mapTile->getFrameHeight(),
				_mapTile->getFrameWidth(),
				_mapTile->getFrameHeight());
		}
	}


	//타일 영역
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			_tiles[i * TILEX + j].rc = D2DMANAGER->RectMake(
				j * _mapTile->getFrameWidth(),
				i * _mapTile->getFrameHeight(),
				_mapTile->getFrameWidth(),
				_mapTile->getFrameHeight());
		}
	}
	for (int i = 0; i < TILEX * TILEY; ++i)
	{
		_tiles[i].terrainFrameX = 3;
		_tiles[i].terrainFrameY = 0;
		_tiles[i].obj1FrameX = 0;
		_tiles[i].obj1FrameY = 0;
		_tiles[i].obj2FrameX = 0;
		_tiles[i].obj2FrameY = 0;
		//_tiles[i].terrain = terrainSelect(_tiles[i].terrainFrameX, _tiles[i].terrainFrameY);
		_tiles[i].obj = OBJ_NONE;
	}
}

void mapTool::setMap()
{
	//타일셋에 내가 그리고싶은 타일 또는 오브젝트 클릭
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; ++i)
	{
		if (PTIN_RECT(&_sampleTile[i].rcTile, _cursor->mouseCursorPoint()))
		{
			_currentTile.x = _sampleTile[i].terrainFrameX;
			_currentTile.y = _sampleTile[i].terrainFrameY;
			break;
		}
	}

	if (!_tileUI._isTouch)
	{
		for (int i = 0; i < TILEX * TILEY; ++i)
		{
			if (PTIN_RECT(&_tiles[i].rc, _cursor->mouseCursorPoint()))
			{
				if (_ctrSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;

					if (_pageNum == PAGE1) _tiles[i].trPage = PAGE1_TR;
					if (_pageNum == PAGE2) _tiles[i].trPage = PAGE2_TR;
					if (_pageNum == PAGE3) _tiles[i].trPage = PAGE3_TR;
					if (_pageNum == PAGE4) _tiles[i].trPage = PAGE4_TR;
					if (_pageNum == PAGE5) _tiles[i].trPage = PAGE5_TR;
					//_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrSelect == CTRL_OBJDRAW1)
				{
					_tiles[i].obj = OBJ_NOT_WALL;

					if (_objectSelect == OBJ_WALL) _tiles[i].obj = OBJ_WALL;

					_tiles[i].obj1FrameX = _currentTile.x;
					_tiles[i].obj1FrameY = _currentTile.y;

					if (_pageNum == PAGE1) _tiles[i].objPage1 = PAGE1_OBJ1;
					if (_pageNum == PAGE2) _tiles[i].objPage1 = PAGE2_OBJ1;
					if (_pageNum == PAGE3) _tiles[i].objPage1 = PAGE3_OBJ1;
					if (_pageNum == PAGE4) _tiles[i].objPage1 = PAGE4_OBJ1;
					if (_pageNum == PAGE5) _tiles[i].objPage1 = PAGE5_OBJ1;
					//_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrSelect == CTRL_OBJDRAW2)
				{
					_tiles[i].obj = OBJ_NOT_WALL;
				
					if (_objectSelect == OBJ_WALL) _tiles[i].obj = OBJ_WALL;
				
					_tiles[i].obj2FrameX = _currentTile.x;
					_tiles[i].obj2FrameY = _currentTile.y;
				
					if (_pageNum == PAGE1) _tiles[i].objPage2 = PAGE1_OBJ2;
					if (_pageNum == PAGE2) _tiles[i].objPage2 = PAGE2_OBJ2;
					if (_pageNum == PAGE3) _tiles[i].objPage2 = PAGE3_OBJ2;
					if (_pageNum == PAGE4) _tiles[i].objPage2 = PAGE4_OBJ2;
					if (_pageNum == PAGE5) _tiles[i].objPage2 = PAGE5_OBJ2;
					//_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
				}
				else if (_ctrSelect == CTRL_ERASER)
				{
					if (_attributeButton[TR_BTN].push) {
						_tiles[i].terrainFrameX = NULL;
						_tiles[i].terrainFrameY = NULL;
						_tiles[i].terrain = TR_NONE;
					}
					else if (_attributeButton[OBJ1_BTN].push) {
						_tiles[i].obj1FrameX = NULL;
						_tiles[i].obj1FrameY = NULL;
						_tiles[i].obj = OBJ_NONE;
						if(_attributeButton[COLLISION_BTN].push) _tiles[i].obj = OBJ_NOT_WALL;
					}
					else if (_attributeButton[OBJ2_BTN].push) {
						_tiles[i].obj2FrameX = NULL;
						_tiles[i].obj2FrameY = NULL;
						_tiles[i].obj = OBJ_NONE;
						if (_attributeButton[COLLISION_BTN].push) _tiles[i].obj = OBJ_NOT_WALL;
					}

				}

				InvalidateRect(_hWnd, NULL, false);
				break;
			}
		}
	}
}

void mapTool::save()
{
	//저장하구
	HANDLE file;
	DWORD write;

	file = CreateFile("mapFile/ongoing.map", GENERIC_WRITE, NULL, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &write, NULL);

	CloseHandle(file);
}

void mapTool::load(int num)
{
	//저장하구
	HANDLE file;
	DWORD read;

	file = NULL;

	if (num == 0) {
		file = CreateFile("mapFile/ongoing.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (num == 1) {
		file = CreateFile("mapFile/start.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (num == 2) {
		file = CreateFile("mapFile/dungeon.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (num == 3) {
		file = CreateFile("mapFile/dungeon2.map", GENERIC_READ, NULL, NULL,
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	ReadFile(file, _tiles, sizeof(tagTile) * TILEX * TILEY, &read, NULL);
	ReadFile(file, _pos, sizeof(int) * 2, &read, NULL);

	memset(_attribute, 0, sizeof(DWORD) * TILEX * TILEY);
	memset(_pos, 0, sizeof(int) * 2);

	CloseHandle(file);
}

void mapTool::ui_update()
{
	_tileUI.rc = D2DMANAGER->RectMake(_tileUI.x + cam_x, _tileUI.y + cam_y, _tileUI.img->getWidth(), _tileUI.img->getHeight());
	_tileUI.bar_rc = D2DMANAGER->RectMake(_tileUI.x + cam_x, _tileUI.y + cam_y, _tileUI.bar_img->getWidth(), _tileUI.bar_img->getHeight());
	_pageButton[PAGE1].rc = D2DMANAGER->RectMake(_tileUI.x + 12 + cam_x, _tileUI.y + 50 + cam_y, _pageButton[PAGE1].img->getWidth(), _pageButton[PAGE1].img->getHeight());
	_pageButton[PAGE2].rc = D2DMANAGER->RectMake(_tileUI.x + 12 + cam_x, _tileUI.y + 120 + cam_y, _pageButton[PAGE2].img->getWidth(), _pageButton[PAGE2].img->getHeight());
	_pageButton[PAGE3].rc = D2DMANAGER->RectMake(_tileUI.x + 12 + cam_x, _tileUI.y + 190 + cam_y, _pageButton[PAGE3].img->getWidth(), _pageButton[PAGE3].img->getHeight());
	_pageButton[PAGE4].rc = D2DMANAGER->RectMake(_tileUI.x + 12 + cam_x, _tileUI.y + 260 + cam_y, _pageButton[PAGE4].img->getWidth(), _pageButton[PAGE4].img->getHeight());
	_pageButton[PAGE5].rc = D2DMANAGER->RectMake(_tileUI.x + 12 + cam_x, _tileUI.y + 330 + cam_y, _pageButton[PAGE5].img->getWidth(), _pageButton[PAGE5].img->getHeight());

	_attributeButton[TR_BTN].rc = D2DMANAGER->RectMake(_tileUI.x + 13 + cam_x, _tileUI.y + 514 + cam_y, _attributeButton[TR_BTN].img->getWidth(), _attributeButton[TR_BTN].img->getHeight());
	_attributeButton[OBJ1_BTN].rc = D2DMANAGER->RectMake(_tileUI.x + 135 + cam_x, _tileUI.y + 514 + cam_y, _attributeButton[OBJ1_BTN].img->getWidth(), _attributeButton[OBJ1_BTN].img->getHeight());
	_attributeButton[OBJ2_BTN].rc = D2DMANAGER->RectMake(_tileUI.x + 274 + cam_x, _tileUI.y + 514 + cam_y, _attributeButton[OBJ2_BTN].img->getWidth(), _attributeButton[OBJ2_BTN].img->getHeight());
	_attributeButton[COLLISION_BTN].rc = D2DMANAGER->RectMake(_tileUI.x + 135 + cam_x, _tileUI.y + 559 + cam_y, _attributeButton[COLLISION_BTN].img->getWidth(), _attributeButton[COLLISION_BTN].img->getHeight());
	_attributeButton[ERASE_BTN].rc = D2DMANAGER->RectMake(_tileUI.x + 274 + cam_x, _tileUI.y + 559 + cam_y, _attributeButton[ERASE_BTN].img->getWidth(), _attributeButton[ERASE_BTN].img->getHeight());

	_textBox[0].rc = D2DMANAGER->RectMake(_tileUI.x + 13 + cam_x, _tileUI.y + 559 + cam_y, _textBox[0].img->getWidth(), _textBox[0].img->getHeight());
	_textBox[1].rc = D2DMANAGER->RectMake(_tileUI.x + 71 + cam_x, _tileUI.y + 559 + cam_y, _textBox[1].img->getWidth(), _textBox[1].img->getHeight());

	_saveButton.rc = D2DMANAGER->RectMake(_tileUI.x + 81 + cam_x, _tileUI.y + 611 + cam_y, _saveButton.img->getWidth(), _saveButton.img->getHeight());
	_saveButton.img = IMAGEMANAGER->findImage("SAVE_BTN");

	_loadButton.rc = D2DMANAGER->RectMake(_tileUI.x + 220 + cam_x, _tileUI.y + 611 + cam_y, _saveButton.img->getWidth(), _saveButton.img->getHeight());
	_loadButton.img = IMAGEMANAGER->findImage("LOAD_BTN");

	_exitButton.rc = D2DMANAGER->RectMake(WINSIZEX - _exitButton.img->getWidth() - 30 + cam_x, 30 + cam_y, _exitButton.img->getWidth(), _exitButton.img->getHeight());
	_exitButton.img = IMAGEMANAGER->findImage("EXIT_BTN_1");

	if (PTIN_RECT(&_tileUI.rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			if (!_tileUI._isTouch)
			{
				clickX = _ptMouse2.x - _tileUI.x;
				clickY = _ptMouse2.y - _tileUI.y;

				_tileUI._isTouch = true;
			}

			currentX = _ptMouse2.x - clickX;
			currentY = _ptMouse2.y - clickY;

			_tileUI.x = currentX;
			_tileUI.y = currentY;

			currentX = currentY = 0;
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_tileUI._isTouch = false;
		}
	}

	if (PTIN_RECT(&_pageButton[PAGE1].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pageNum = PAGE1;
		}
	}
	else if (PTIN_RECT(&_pageButton[PAGE2].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pageNum = PAGE2;
		}
	}
	else if (PTIN_RECT(&_pageButton[PAGE3].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pageNum = PAGE3;
		}
	}
	else if (PTIN_RECT(&_pageButton[PAGE4].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pageNum = PAGE4;
		}
	}
	else if (PTIN_RECT(&_pageButton[PAGE5].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_pageNum = PAGE5;
		}
	}
	else if (PTIN_RECT(&_attributeButton[TR_BTN].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_attributeButton[TR_BTN].push) {
				_ctrSelect = CTRL_TERRAINDRAW;
				_attributeButton[TR_BTN].push = true;
			}
			else if (_attributeButton[TR_BTN].push) {
				_ctrSelect = CTRL_END;
				_attributeButton[TR_BTN].push = false;
			}
		}
	}
	else if (PTIN_RECT(&_attributeButton[OBJ1_BTN].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_attributeButton[OBJ1_BTN].push) {
				_ctrSelect = CTRL_OBJDRAW1;
				_attributeButton[OBJ1_BTN].push = true;
			}
			else if (_attributeButton[OBJ1_BTN].push) {
				_ctrSelect = CTRL_END;
				_attributeButton[OBJ1_BTN].push = false;
			}
		}
	}
	else if (PTIN_RECT(&_attributeButton[OBJ2_BTN].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_attributeButton[OBJ2_BTN].push) {
				_ctrSelect = CTRL_OBJDRAW2;
				_attributeButton[OBJ2_BTN].push = true;
			}
			else if (_attributeButton[OBJ2_BTN].push) {
				_ctrSelect = CTRL_TERRAINDRAW;
				_attributeButton[OBJ2_BTN].push = false;
			}
		}
	}
	else if (PTIN_RECT(&_attributeButton[COLLISION_BTN].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_attributeButton[COLLISION_BTN].push) {
				_objectSelect = OBJ_WALL;
				_attributeButton[COLLISION_BTN].push = true;
			}
			else if (_attributeButton[COLLISION_BTN].push) {
				_objectSelect = OBJ_NOT_WALL;
				_attributeButton[COLLISION_BTN].push = false;
			}
		}
	}
	else if (PTIN_RECT(&_attributeButton[ERASE_BTN].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_attributeButton[ERASE_BTN].push) {
				_ctrSelect = CTRL_ERASER;
				_objectSelect = OBJ_NOT_WALL;
				_attributeButton[ERASE_BTN].push = true;
			}
			else if (_attributeButton[ERASE_BTN].push) {

				if (_attributeButton[TR_BTN].push) _ctrSelect = CTRL_TERRAINDRAW;
				else if (_attributeButton[OBJ1_BTN].push) _ctrSelect = CTRL_OBJDRAW1;
				else if (_attributeButton[OBJ2_BTN].push) _ctrSelect = CTRL_OBJDRAW2;
				else { _ctrSelect = CTRL_END; }
				_attributeButton[ERASE_BTN].push = false;
			}
		}
	}
	else if (PTIN_RECT(&_saveButton.rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			save();
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
			_saveButton.img = IMAGEMANAGER->findImage("SAVE_BTN_PUSH");
		}
	}
	else if (PTIN_RECT(&_loadButton.rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			load(0);
		}
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
			_loadButton.img = IMAGEMANAGER->findImage("LOAD_BTN_PUSH");
		}
	}
	else if (PTIN_RECT(&_textBox[0].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_textBox[1].push) {
			_textBox[0].push = true;
		}
	}
	else if (PTIN_RECT(&_textBox[1].rc, _cursor->mouseCursorPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_textBox[0].push) {
			_textBox[1].push = true;
		}
	}

	if (PTIN_RECT(&_exitButton.rc, _cursor->mouseCursorPoint()))
	{
		_exitButton.img = IMAGEMANAGER->findImage("EXIT_BTN_2");

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_tileUI._isTouch = true;
			_exitButton.img = IMAGEMANAGER->findImage("EXIT_BTN_3");
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			_tileUI._isTouch = false;
			SCENEMANAGER->changeScene("타이틀");
		}
	}



	if (_ctrSelect == CTRL_TERRAINDRAW) {
		_attributeButton[TR_BTN].img = IMAGEMANAGER->findImage("TR_BTN_PUSH");
		_objectSelect = OBJ_NOT_WALL;

		if (_attributeButton[ERASE_BTN].push) {
			_ctrSelect = CTRL_ERASER;
			_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->findImage("OBJ1_BTN");
			_attributeButton[OBJ1_BTN].push = false;
			_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->findImage("OBJ2_BTN");
			_attributeButton[OBJ2_BTN].push = false;
		}
	}
	else if (_ctrSelect != CTRL_TERRAINDRAW && !_attributeButton[ERASE_BTN].push) {
		_attributeButton[TR_BTN].img = IMAGEMANAGER->findImage("TR_BTN");
		_attributeButton[TR_BTN].push = false;
	}

	if (_ctrSelect == CTRL_OBJDRAW1) {
		_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->findImage("OBJ1_BTN_PUSH");
		
		if (_attributeButton[ERASE_BTN].push) {
			_ctrSelect = CTRL_ERASER;
			_attributeButton[TR_BTN].img = IMAGEMANAGER->findImage("TR_BTN");
			_attributeButton[TR_BTN].push = false;
			_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->findImage("OBJ2_BTN");
			_attributeButton[OBJ2_BTN].push = false;
		}
	}
	else if (_ctrSelect != CTRL_OBJDRAW1 && !_attributeButton[ERASE_BTN].push) {
		_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->findImage("OBJ1_BTN");
		_attributeButton[OBJ1_BTN].push = false;
	}

	if (_ctrSelect == CTRL_OBJDRAW2) {
		_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->findImage("OBJ2_BTN_PUSH");

		if (_attributeButton[ERASE_BTN].push) {
			_ctrSelect = CTRL_ERASER;
			_attributeButton[TR_BTN].img = IMAGEMANAGER->findImage("TR_BTN");
			_attributeButton[TR_BTN].push = false;
			_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->findImage("OBJ1_BTN");
			_attributeButton[OBJ1_BTN].push = false;
		}
	}
	else if (_ctrSelect != CTRL_OBJDRAW2 && !_attributeButton[ERASE_BTN].push) {
		_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->findImage("OBJ2_BTN");
		_attributeButton[OBJ2_BTN].push = false;
	}

	if (_objectSelect == OBJ_WALL) {
		_attributeButton[COLLISION_BTN].img = IMAGEMANAGER->findImage("COLLISION_BTN_PUSH");
	}
	else if (_objectSelect != OBJ_WALL) {
		_attributeButton[COLLISION_BTN].img = IMAGEMANAGER->findImage("COLLISION_BTN");
		_attributeButton[COLLISION_BTN].push = false;
	}

	if (_ctrSelect == CTRL_ERASER) {
		_attributeButton[ERASE_BTN].img = IMAGEMANAGER->findImage("ERASE_BTN_PUSH");
	}
	else if (_ctrSelect != CTRL_ERASER) {
		_attributeButton[ERASE_BTN].img = IMAGEMANAGER->findImage("ERASE_BTN");
		_attributeButton[ERASE_BTN].push = false;
	}


	if (_textBox[0].push) {
		_textBox[0].img = IMAGEMANAGER->findImage("textBox2");

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_textBox[0].push = false;

			int text1_num = atoi(_textBox[0].str);
			int text2_num = atoi(_textBox[1].str);

			changeSize(text1_num, text2_num);
		}
	}
	else if (!_textBox[0].push) {
		_textBox[0].img = IMAGEMANAGER->findImage("textBoxX");

	}

	if (_textBox[1].push) {
		_textBox[1].img = IMAGEMANAGER->findImage("textBox2");

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_textBox[1].push = false;
			
			int text1_num = atoi(_textBox[0].str);
			int text2_num = atoi(_textBox[1].str);

			changeSize(text1_num, text2_num);
		}
	}
	else if (!_textBox[1].push) {
		_textBox[1].img = IMAGEMANAGER->findImage("textBoxY");

	}
}

void mapTool::ui_render()
{
	//맵툴 윈도우창
	_tileUI.img->render(_tileUI.x + cam_x, _tileUI.y + cam_y);
	_tileUI.bar_img->render(_tileUI.x + cam_x, _tileUI.y + cam_y);
	_pageButton[PAGE1].img->render(_tileUI.x + 12 + cam_x, _tileUI.y + 50 + cam_y);
	_pageButton[PAGE2].img->render(_tileUI.x + 12 + cam_x, _tileUI.y + 120 + cam_y);
	_pageButton[PAGE3].img->render(_tileUI.x + 12 + cam_x, _tileUI.y + 190 + cam_y);
	_pageButton[PAGE4].img->render(_tileUI.x + 12 + cam_x, _tileUI.y + 260 + cam_y);
	_pageButton[PAGE5].img->render(_tileUI.x + 12 + cam_x, _tileUI.y + 330 + cam_y);

	_attributeButton[TR_BTN].img->render(_tileUI.x + 13 + cam_x, _tileUI.y + 514 + cam_y);
	_attributeButton[OBJ1_BTN].img->render(_tileUI.x + 135 + cam_x, _tileUI.y + 514 + cam_y);
	_attributeButton[OBJ2_BTN].img->render(_tileUI.x + 274 + cam_x, _tileUI.y + 514 + cam_y);
	_attributeButton[COLLISION_BTN].img->render(_tileUI.x + 135 + cam_x, _tileUI.y + 559 + cam_y);
	_attributeButton[ERASE_BTN].img->render(_tileUI.x + 274 + cam_x, _tileUI.y + 559 + cam_y);

	_textBox[0].img->render(_tileUI.x + 13 + cam_x, _tileUI.y + 559 + cam_y);
	_textBox[1].img->render(_tileUI.x + 71 + cam_x, _tileUI.y + 559 + cam_y);

	_saveButton.img->render(_tileUI.x + 81 + cam_x, _tileUI.y + 611 + cam_y);
	_loadButton.img->render(_tileUI.x + 220 + cam_x, _tileUI.y + 611 + cam_y);

	_exitButton.img->render(WINSIZEX - _exitButton.img->getWidth() - 30 + cam_x, 30 + cam_y);

	//UI에 들어있는 맵타일 이미지
	for (int i = 0; i < SAMPLETILEY; i++)
	{
		for (int j = 0; j < SAMPLETILEX; j++)
		{
			if(_pageNum == PAGE1)
			_sampleMapTile->FrameRender((_tileUI.x + 124) + j * _sampleMapTile->getFrameWidth() + cam_x, (_tileUI.y + 51) + i * _sampleMapTile->getFrameHeight() + cam_y, j, i);
		
			if(_pageNum == PAGE2)
			_sampleMapTile2->FrameRender((_tileUI.x + 124) + j * _sampleMapTile->getFrameWidth() + cam_x, (_tileUI.y + 51) + i * _sampleMapTile->getFrameHeight() + cam_y, j, i);

			if (_pageNum == PAGE3)
			_sampleMapTile3->FrameRender((_tileUI.x + 124) + j * _sampleMapTile->getFrameWidth() + cam_x, (_tileUI.y + 51) + i * _sampleMapTile->getFrameHeight() + cam_y, j, i);

			if (_pageNum == PAGE4)
			_sampleMapTile4->FrameRender((_tileUI.x + 124) + j * _sampleMapTile->getFrameWidth() + cam_x, (_tileUI.y + 51) + i * _sampleMapTile->getFrameHeight() + cam_y, j, i);

			if (_pageNum == PAGE5)
			_sampleMapTile5->FrameRender((_tileUI.x + 124) + j * _sampleMapTile->getFrameWidth() + cam_x, (_tileUI.y + 51) + i * _sampleMapTile->getFrameHeight() + cam_y, j, i);
		}
	}

	//UI 맵타일 렉트
	for (int i = 0; i < SAMPLETILEX * SAMPLETILEY; i++) {
		if (!_tileUI._isTouch) {
			D2DMANAGER->Rectangle(_sampleTile[i].rcTile, 0.2f);

			if (_sampleTile[i].terrainFrameX == _currentTile.x && _sampleTile[i].terrainFrameY == _currentTile.y) {
				D2DMANAGER->Rectangle_brush(D2DMANAGER->CreateBrush(0xFF0000), _sampleTile[i].rcTile);
			}
		}
	}

	//선택타일 미리보기
	if (_pageNum == PAGE1_TR || _pageNum == PAGE1_OBJ1 || _pageNum == PAGE1_OBJ2) _mapTile->FrameRender(_tileUI.x + 20 + cam_x, _tileUI.y + 410 + cam_y, _currentTile.x, _currentTile.y);
	if (_pageNum == PAGE2_TR || _pageNum == PAGE2_OBJ1 || _pageNum == PAGE2_OBJ2) _mapTile2->FrameRender(_tileUI.x + 20 + cam_x, _tileUI.y + 410 + cam_y, _currentTile.x, _currentTile.y);
	if (_pageNum == PAGE3_TR || _pageNum == PAGE3_OBJ1 || _pageNum == PAGE3_OBJ2) _mapTile3->FrameRender(_tileUI.x + 20 + cam_x, _tileUI.y + 410 + cam_y, _currentTile.x, _currentTile.y);
	if (_pageNum == PAGE4_TR || _pageNum == PAGE4_OBJ1 || _pageNum == PAGE4_OBJ2) _mapTile4->FrameRender(_tileUI.x + 20 + cam_x, _tileUI.y + 410 + cam_y, _currentTile.x, _currentTile.y);
	if (_pageNum == PAGE5_TR || _pageNum == PAGE5_OBJ1 || _pageNum == PAGE5_OBJ2) _mapTile5->FrameRender(_tileUI.x + 20 + cam_x, _tileUI.y + 410 + cam_y, _currentTile.x, _currentTile.y);

	if (_textBox[0].push) {
		strcpy_s(_textBox[0].str, _char);

		for (int i = 2; i < 256; i++)
		{
			_textBox[0].str[i] = 0;
		}

	}

	if (_textBox[1].push) {
		strcpy_s(_textBox[1].str, _char);

		for (int i = 2; i < 256; i++)
		{
			_textBox[1].str[i] = 0;
		}

	}

	WCHAR text1[256];
	WCHAR text2[256];

	swprintf_s(text1, L"%S", _textBox[0].str);
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0x000000), L"둥근모꼴", 17.0f, text1
		, _tileUI.x + 13
		, _tileUI.y + 559 + 6
		, _tileUI.x + 13 + _textBox[0].img->getWidth()
		, _tileUI.y + 559 + _textBox[0].img->getHeight());

	swprintf_s(text2, L"%S", _textBox[1].str);
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0x000000), L"둥근모꼴", 17.0f, text2
		, _tileUI.x + 71
		, _tileUI.y + 559 + 6
		, _tileUI.x + 71 + _textBox[1].img->getWidth()
		, _tileUI.y + 559 + _textBox[1].img->getHeight());
}

void mapTool::changeSize(int x, int y)
{
	CAMERAMANAGER->init(81 * x, 81 * y);

	TILEX = x;
	TILEY = y;

	setup();
}

HRESULT mapTool::init(int x, int y)
{
	CAMERAMANAGER->init(81 * x, 81 * y);

	TILEX = x;
	TILEY = y;

	_cursor = new mouseCursor;
	_cursor->init();

	_mapTile = IMAGEMANAGER->addFrameImage("MapTiles1", L"image/mapTool/maptiles1.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile2 = IMAGEMANAGER->addFrameImage("MapTiles2", L"image/mapTool/maptiles2.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile3 = IMAGEMANAGER->addFrameImage("MapTiles3", L"image/mapTool/maptiles3.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile4 = IMAGEMANAGER->addFrameImage("MapTiles4", L"image/mapTool/maptiles4.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_mapTile5 = IMAGEMANAGER->addFrameImage("MapTiles5", L"image/mapTool/maptiles5.png", 384 * TILE_SCALE, 768 * TILE_SCALE, SAMPLETILEX, SAMPLETILEY);

	_sampleMapTile = IMAGEMANAGER->addFrameImage("sampleMapTiles1", L"image/mapTool/maptiles1.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile2 = IMAGEMANAGER->addFrameImage("sampleMapTiles2", L"image/mapTool/mapTiles2.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile3 = IMAGEMANAGER->addFrameImage("sampleMapTiles3", L"image/mapTool/mapTiles3.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile4 = IMAGEMANAGER->addFrameImage("sampleMapTiles4", L"image/mapTool/mapTiles4.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);
	_sampleMapTile5 = IMAGEMANAGER->addFrameImage("sampleMapTiles5", L"image/mapTool/mapTiles5.png", 384 * SAMPLETILE_SCALE, 768 * SAMPLETILE_SCALE, SAMPLETILEX, SAMPLETILEY);

	_pageButton[PAGE1].img = IMAGEMANAGER->addImage("PAGE1_BUTTON", L"image/mapTool/PAGE1_BUTTON.png", 98, 63);
	_pageButton[PAGE2].img = IMAGEMANAGER->addImage("PAGE2_BUTTON", L"image/mapTool/PAGE2_BUTTON.png", 98, 63);
	_pageButton[PAGE3].img = IMAGEMANAGER->addImage("PAGE3_BUTTON", L"image/mapTool/PAGE3_BUTTON.png", 98, 63);
	_pageButton[PAGE4].img = IMAGEMANAGER->addImage("PAGE4_BUTTON", L"image/mapTool/PAGE4_BUTTON.png", 98, 63);
	_pageButton[PAGE5].img = IMAGEMANAGER->addImage("PAGE5_BUTTON", L"image/mapTool/PAGE5_BUTTON.png", 98, 63);

	_attributeButton[TR_BTN].img = IMAGEMANAGER->addImage("TR_BTN", L"image/mapTool/TERRAIN_BUTTON.png", 109, 32);
	IMAGEMANAGER->addImage("TR_BTN_PUSH", L"image/mapTool/TERRAIN_BUTTON_PUSH.png", 109, 32);

	_attributeButton[OBJ1_BTN].img = IMAGEMANAGER->addImage("OBJ1_BTN", L"image/mapTool/OBJ1_BUTTON.png", 126, 32);
	IMAGEMANAGER->addImage("OBJ1_BTN_PUSH", L"image/mapTool/OBJ1_BUTTON_PUSH.png", 126, 32);

	_attributeButton[OBJ2_BTN].img = IMAGEMANAGER->addImage("OBJ2_BTN", L"image/mapTool/OBJ2_BUTTON.png", 112, 32);
	IMAGEMANAGER->addImage("OBJ2_BTN_PUSH", L"image/mapTool/OBJ2_BUTTON_PUSH.png", 112, 32);

	_attributeButton[COLLISION_BTN].img = IMAGEMANAGER->addImage("COLLISION_BTN", L"image/mapTool/COLLISION_BUTTON.png", 126, 32);
	IMAGEMANAGER->addImage("COLLISION_BTN_PUSH", L"image/mapTool/COLLISION_BUTTON_PUSH.png", 126, 32);

	_attributeButton[ERASE_BTN].img = IMAGEMANAGER->addImage("ERASE_BTN", L"image/mapTool/ERASE_BUTTON.png", 112, 32);
	IMAGEMANAGER->addImage("ERASE_BTN_PUSH", L"image/mapTool/ERASE_BUTTON_PUSH.png", 112, 32);

	_saveButton.img = IMAGEMANAGER->addImage("SAVE_BTN", L"image/mapTool/SAVE_BUTTON.png", 96, 31);
	IMAGEMANAGER->addImage("SAVE_BTN_PUSH", L"image/mapTool/SAVE_BUTTON_PUSH.png", 96, 31);

	_loadButton.img = IMAGEMANAGER->addImage("LOAD_BTN", L"image/mapTool/LOAD_BUTTON.png", 96, 31);
	IMAGEMANAGER->addImage("LOAD_BTN_PUSH", L"image/mapTool/LOAD_BUTTON_PUSH.png", 96, 31);

	IMAGEMANAGER->addImage("textBoxX", L"image/mapTool/textBoxX.png", 51, 32);
	IMAGEMANAGER->addImage("textBoxY", L"image/mapTool/textBoxY.png", 51, 32);
	IMAGEMANAGER->addImage("textBox2", L"image/mapTool/textBox1_push.png", 51, 32);

	_textBox[0].img = IMAGEMANAGER->findImage("textBoxX");
	_textBox[1].img = IMAGEMANAGER->findImage("textBoxY");

	_tileUI.img = IMAGEMANAGER->addImage("mapTool_window", L"image/mapTool/mapWindow.png", 397, 660);
	_tileUI.bar_img = IMAGEMANAGER->addImage("mapTool_bar", L"image/mapTool/mapWindowBar.png", 397, 35);

	_tileUI.x = 1090;
	_tileUI.y = 110;

	_exitButton.img = IMAGEMANAGER->addImage("EXIT_BTN_1", L"image/mapTool/EXIT_BUTTON_1.png", 178, 46);
	IMAGEMANAGER->addImage("EXIT_BTN_2", L"image/mapTool/EXIT_BUTTON_2.png", 178, 46);
	IMAGEMANAGER->addImage("EXIT_BTN_3", L"image/mapTool/EXIT_BUTTON_3.png", 178, 46);

	setup();

	return S_OK;
}

//TERRAIN mapTool::terrainSelect(int frameX, int frameY)
//{
//	if (frameX == 1 && frameY == 0)
//	{
//		return TR_CEMENT;
//	}
//	else if (frameX == 2 && frameY == 0)
//	{
//		return TR_DESERT;
//	}
//	else if (frameX == 3 && frameY == 0)
//	{
//		return TR_GRASS;
//	}
//	else if (frameX == 4 && frameY == 0)
//	{
//		return TR_WATER;
//	}
//
//	return TR_GRASS;
//
//}

//OBJECT mapTool::objSelect(int frameX, int frameY)
//{
//	if (frameX == 0 && frameY == 0)
//	{
//		return OBJ_TANK1;
//	}
//	else if (frameX == 0 && frameY == 8)
//	{
//		return OBJ_TANK2;
//	}
//	else if (frameX == 0 && frameY == 1)
//	{
//		return OBJ_BLOCK1;
//	}
//	else if (frameX == 0 && frameY == 2)
//	{
//		return OBJ_BLOCK3;
//	}
//	else if (frameX == 15 && frameY == 3)
//	{
//		return OBJ_BLOCKS;
//	}
//
//	return OBJ_BLOCK1;
//}