#pragma once
#include "stdafx.h"

enum mouseCursor_state
{
	basic,
	aim,

	cursorNum
};

class mouseCursor
{
private:

	float cam_x;
	float cam_y;

	image* mouseCursor;
	int mouseCursorX, mouseCursorY;

	POINT ptMouseCursor;

	int _cursorNum;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	float getCursorX() { return ptMouseCursor.x; }
	float getCursorY() { return ptMouseCursor.y; }

	POINT mouseCursorPoint() { return ptMouseCursor; }
};

