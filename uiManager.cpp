#include "stdafx.h"
#include "uiManager.h"

HRESULT UiManager::init()
{
	ui = INTRO_SCREEN;

	player_info_manager.max_hp = 100;
	player_info_manager.current_hp = 100;
	player_info_manager.max_mp = 100;
	player_info_manager.current_mp = 100;
	player_info_manager.max_stamina = 100;
	player_info_manager.current_stamina = 100;

	return S_OK;
}

void UiManager::release()
{
}

void UiManager::changeUI(int CURRENT_UI)
{
	ui = CURRENT_UI;
}

void UiManager::Save(player* _player, mapTool* _mapTool)
{
	player_info_manager.max_hp = _player->getTagPlayerInfo().max_hp;
	player_info_manager.current_hp = _player->getTagPlayerInfo().current_hp;
	player_info_manager.max_mp = _player->getTagPlayerInfo().max_mp;
	player_info_manager.current_mp = _player->getTagPlayerInfo().current_mp;
	player_info_manager.max_stamina = _player->getTagPlayerInfo().max_stamina;
	player_info_manager.current_stamina = _player->getTagPlayerInfo().current_stamina;
}

void UiManager::Load(player* _player, mapTool* _mapTool)
{
	_player->setTagPlayerInfo()->max_hp = player_info_manager.max_hp;
	_player->setTagPlayerInfo()->current_hp = player_info_manager.current_hp;
	_player->setTagPlayerInfo()->max_mp = player_info_manager.max_mp;
	_player->setTagPlayerInfo()->current_mp = player_info_manager.current_mp;
	_player->setTagPlayerInfo()->max_stamina = player_info_manager.max_stamina;
	_player->setTagPlayerInfo()->current_stamina = player_info_manager.current_stamina;
	
	map_info_manager.X = _mapTool->getTileX();
	map_info_manager.Y = _mapTool->getTileY();
}
