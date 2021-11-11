#pragma once
#include "gameNode.h"

class mapChange : public gameNode
{
private:
	

public:

	HRESULT init();
	void release();
	void update();
	void render();
};

