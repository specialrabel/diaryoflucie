#include "stdafx.h"
#include "player.h"
#include "cameraState.h"

STATE * CameraState::inputHandle(player* player)
{
	return nullptr;
}

void CameraState::update(player* player)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setTagPlayer()->x -= player->getTagPlayerInfo().speed;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setTagPlayer()->x += player->getTagPlayerInfo().speed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setTagPlayer()->y -= player->getTagPlayerInfo().speed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setTagPlayer()->y += player->getTagPlayerInfo().speed;
	}
}

void CameraState::enter(player * player)
{
}

void CameraState::exit(player * player)
{
}
