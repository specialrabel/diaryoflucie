#pragma once
#include "player.h"

struct TABMAP
{
	image* icon;
	image* up;
	image* down;
	image* left;
	image* right;
};

class ui
{
private:
	player* _player;

	bool tabMap_bool;
	image* tabMap_window;

	TABMAP tabMap[MAP_MAX];
	image* tabMap_icon[MAP_MAX];
	image* tabMap_current;

	image* status_case;
	image* status_hp;
	image* status_mp;
	image* status_stamina;

	float cam_x;
	float cam_y;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

