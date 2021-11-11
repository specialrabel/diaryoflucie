#include "stdafx.h"
#include "mapChange.h"

HRESULT mapChange::init()
{
	return S_OK;
}

void mapChange::release()
{
}

void mapChange::update()
{
	if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).type == RANDOM_MAP::START_MAP)			SCENEMANAGER->changeScene("���۸�");
	else if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).type == RANDOM_MAP::DUNGEON1_MAP)	SCENEMANAGER->changeScene("����");
	else if (MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).type == RANDOM_MAP::DUNGEON2_MAP)	SCENEMANAGER->changeScene("����2");

}

void mapChange::render()
{
}
