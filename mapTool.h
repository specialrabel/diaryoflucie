#pragma once
#include "gameNode.h"
#include "tileNode.h"
#include "player.h"
#include "mouseCursor.h"

struct tileUI
{
	D2D1_RECT_F rc;
	image* img;
	int x, y;
	int width, height;
	bool _isTouch;
	
	D2D1_RECT_F bar_rc;
	image* bar_img;
	int bar_x, bar_y;
};

struct exitButton
{
	image* img;
	D2D1_RECT_F rc;
	bool in, push;
};

struct attributeButton
{
	image* img;
	D2D1_RECT_F rc;
	bool push;
};

struct textBox
{
	image* img;
	D2D1_RECT_F rc;
	bool push;
	CHAR str[256];
};

enum attributeButton_Num
{
	TR_BTN, OBJ1_BTN, OBJ2_BTN, COLLISION_BTN, ERASE_BTN, ATTRIBUTE_BUTTON_END
};

class mapTool : public gameNode
{
private:

	mouseCursor* _cursor;
	player* _player;

	tileUI _tileUI;
	int clickX, clickY, currentX, currentY;

	exitButton _exitButton;

	saveButton _saveButton;
	loadButton _loadButton;
	pageButton _pageButton[PAGE_NUM_END];
	attributeButton _attributeButton[ATTRIBUTE_BUTTON_END];
	textBox _textBox[2];

	tagCurrentTile _currentTile;
	tagSampleTile _sampleTile[SAMPLETILEX * SAMPLETILEY];

	tagTile _tiles[TILEX_ * TILEY_];
	DWORD _attribute[TILEX_ * TILEY_];
	int TILEX = 100;
	int TILEY = 100;

	int _pos[2];
	int _objectSelect;

	image* _sampleMapTile;
	image* _sampleMapTile2;
	image* _sampleMapTile3;
	image* _sampleMapTile4;
	image* _sampleMapTile5;

	image* _mapTile;
	image* _mapTile2;
	image* _mapTile3;
	image* _mapTile4;
	image* _mapTile5;

	float cam_x;
	float cam_y;

	int _pageNum;

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void setup();
	virtual void setMap();

	virtual void save();
	virtual void load(int num);

	void ui_update();
	void ui_render();

	void changeSize(int x, int y);

	virtual HRESULT init(int x, int y);

	tagTile* getTile() { return _tiles; }

	DWORD* getTileAttribute() { return _attribute; }

	//TERRAIN terrainSelect(int frameX, int frameY);
	//OBJECT objSelect(int frameX, int frameY);

	int getTileX() { return TILEX; }
	int getTileY() { return TILEY; }
};

