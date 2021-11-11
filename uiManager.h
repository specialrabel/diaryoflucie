#pragma once
#include "stdafx.h"
#include "singletonBase.h"
#include "player.h"
#include "mapTool.h"

enum CURRENT_UI
{
	INTRO_SCREEN,
	MAIN_SCREEN,
	MAPTOOL_SCREEN,
	HOUSE_SCREEN,
	PLAYING_SCREEN,
	OPTION_SCREEN
};

struct PLAYER_INFO_MANAGER
{
	int max_hp, max_mp, max_stamina;
	float current_hp, current_mp, current_stamina;
};

struct MAP_INFO_MANAGER
{
	int X, Y;
};

class UiManager : public singletonBase<UiManager>
{
private:
	PLAYER_INFO_MANAGER player_info_manager;
	player _player;

	MAP_INFO_MANAGER map_info_manager;
	mapTool _mapTool;

	int ui;

public:
	HRESULT init();
	void release();

	void changeUI(int CURRENT_UI);
	int currentUI() { return ui; }

	void Save(player* _player, mapTool* _mapTool);
	void Load(player* _player, mapTool* _mapTool);

	PLAYER_INFO_MANAGER getTagPlayerInfoManager() { return player_info_manager; }
	MAP_INFO_MANAGER getTagMapInfoManager() { return map_info_manager; }
};