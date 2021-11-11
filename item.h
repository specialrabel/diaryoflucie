#pragma once
#include "gameNode.h"

class item : public gameNode
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();
};

