#pragma once
#include "gameNode.h"
#include "mouseCursor.h"

#define MENU_MAX 4

class title : public gameNode
{
private:

	mouseCursor* _cursor;

	image* gif1;
	image* gif2;
	image* gif3;
	image* title_IMG;
	
	image* text_IMG;
	float text_opacity;

	bool _isEnd_intro;

	image* menu_IMG;
	D2D1_RECT_F menu_RC;
	float menu_move;
	bool menu_move_dir;
	int menu_index;
	image* menu_leftPreview_IMG;
	image* menu_rightPreview_IMG;
	
	image* leftBtn_IMG;
	D2D1_RECT_F leftBtn_RC;

	image* rightBtn_IMG;
	D2D1_RECT_F rightBtn_RC;
	
	bool menu_click_erase;
	bool leftBtn_click_erase;
	bool rightBtn_click_erase;

public:
	HRESULT init();
	void release();
	void update();
	void render();

};

