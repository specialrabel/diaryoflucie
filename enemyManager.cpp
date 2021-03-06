#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"
#include "mapTool.h"

HRESULT enemyManager::init()
{
	update_count = 1.0;

	UIMANAGER->Save(_player, _map);
	UIMANAGER->Load(_player, _map);

	_vTotalList.reserve(UIMANAGER->getTagMapInfoManager().X * UIMANAGER->getTagMapInfoManager().Y);

	for (int i = 0; i < UIMANAGER->getTagMapInfoManager().Y; i++)
	{
		for (int j = 0; j < UIMANAGER->getTagMapInfoManager().X; j++)
		{
			tile* node = new tile;
			node->init(j, i, _map->getTile()[j + UIMANAGER->getTagMapInfoManager().X * i].rc);

			if (((_map->getTileAttribute()[j + UIMANAGER->getTagMapInfoManager().X * i] & ATTR_UNMOVE) == ATTR_UNMOVE))
			{
				node->setAttribute("wall");
			}

			_vTotalList.push_back(node);
		}
	}

	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	update_count += TIMEMANAGER->getElapsedTime();

	if (update_count >= 0.5f)
	{
		find_player();
		find_path();
		update_count = 0.0f;
	}

	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->update();

		D2D1_RECT_F player = _player->getTagPlayer().rc;
		D2D1_RECT_F enemy = (*_pool_iter)->get_rect();

		if (INTERSECTION_RECT(temp, player, enemy))
		{
			(*_pool_iter)->set_arrived(true);
		}
		else
			(*_pool_iter)->set_arrived(false);
	}

	for (int i = 0; i < _enemy_pool.size(); i++)
	{
		if (_enemy_pool[i]->get_hp() <= 0)
		{
			remove_enemy(i);
		}
	}
}

void enemyManager::render()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		(*_pool_iter)->render();
	}
}

//void enemyManager::set_bats(float x, float y)
//{
//	enemy* _bat = new bat;
//	_bat->init(x, y);
//	_enemy_pool.push_back(_bat);
//}
//
//void enemyManager::set_ticks(float x, float y)
//{
//	enemy* _tick = new tick;
//	_tick->init(x, y);
//	_enemy_pool.push_back(_tick);
//}
//
//void enemyManager::set_skeletons(float x, float y)
//{
//	enemy* _skeleton = new skeleton;
//	_skeleton->init(x, y);
//	_enemy_pool.push_back(_skeleton);
//}

void enemyManager::set_maggots(float x, float y)
{
	enemy* _maggot = new maggot;
	_maggot->init(x, y);
	_enemy_pool.push_back(_maggot);
}

void enemyManager::find_path()
{
	for (int i = 0; i < _enemy_pool.size(); i++)
	{
		if (!_enemy_pool[i]->get_find_player()) continue;

		if (_enemy_pool[i]->get_kind() == enemy_kind::BATS)
		{
			_enemy_pool[i]->set_destination(_player->getTagPlayer().rc);
			continue;
		}

		reset();

		int player_tileX = _player->getTagPlayer().x / TILESIZE;
		int player_tileY = _player->getTagPlayer().y / TILESIZE;

		int index = player_tileX + player_tileY * UIMANAGER->getTagMapInfoManager().X;

		_startTile = _vTotalList[index];
		_startTile->setAttribute("end");

		int enemy_tileX = _enemy_pool[i]->get_rect().left / TILESIZE;
		int enemy_tileY = _enemy_pool[i]->get_rect().top / TILESIZE;

		int enemy_index = enemy_tileX + enemy_tileY * UIMANAGER->getTagMapInfoManager().X;

		if (index == enemy_index)
		{
			reset();
			continue;
		}

		_endtile = _vTotalList[enemy_index];
		_endtile->setAttribute("start");

		_currentTile = _endtile;

		reset_list.push_back(index);
		reset_list.push_back(enemy_index);

		if (!_FindPath)
			pathFinder(_currentTile, _vOpenList, _vCloseList);

		if (_vCloseList.size() != 0 && _FindPath)
		{
			_enemy_pool[i]->vector_clear();
			_enemy_pool[i]->set_index(_vCloseList.size() - 1);
			_enemy_pool[i]->set_destination(_player->getTagPlayer().rc);
			for (int j = 0; j < _vCloseList.size(); j++)
			{
				D2D1_RECT_F test = _vCloseList[j]->getRectangle();
				_enemy_pool[i]->get_list().push_back(_vCloseList[j]->getRectangle());
			}
		}
		if (_vCloseList.size() == 0 && _FindPath)
		{
			_enemy_pool[i]->set_destination(_player->getTagPlayer().rc);
		}
	}
}

void enemyManager::reset()
{
	_FindPath = false;
	_vOpenList.clear();
	_vCloseList.clear();

	for (int i = 0; i < reset_list.size(); i++)
	{
		_vTotalList[reset_list[i]]->setParentNode(NULL);
		_vTotalList[reset_list[i]]->setAttribute("NULL");
		_vTotalList[reset_list[i]]->setIsOpen(true);
	}

	reset_list.clear();

}

void enemyManager::remove_enemy(int num)
{
	_enemy_pool.erase(_enemy_pool.begin() + num);
}

void enemyManager::find_player()
{
	for (_pool_iter = _enemy_pool.begin(); _pool_iter != _enemy_pool.end(); ++_pool_iter)
	{
		int x = (*_pool_iter)->get_rect().left + ((*_pool_iter)->get_rect().right - (*_pool_iter)->get_rect().left) / 2;
		int y = (*_pool_iter)->get_rect().top + ((*_pool_iter)->get_rect().bottom - (*_pool_iter)->get_rect().top) / 2;

		int x2 = _player->getTagPlayer().rc.left + (_player->getTagPlayer().rc.right - _player->getTagPlayer().rc.left) / 2;
		int y2 = _player->getTagPlayer().rc.top + (_player->getTagPlayer().rc.bottom - _player->getTagPlayer().rc.top) / 2;

		if (getDistance(x, y, x2, y2) < 450)
		{
			// ???????? ???? ?????? ??
			(*_pool_iter)->set_find_player(true);
		}
		else if (getDistance(x, y, x2, y2) > 500)
		{
			(*_pool_iter)->set_find_player(false);
		}
	}
}

vector<tile*> enemyManager::addOpenList(tile* currentTile, vector<tile*>& openlist)
{
	int startX = currentTile->getIdX() - 1;

	if (startX < 0)
	{
		startX = 0;
	}
	if (startX >= UIMANAGER->getTagMapInfoManager().X - 3)
	{
		startX = UIMANAGER->getTagMapInfoManager().X - 3;
	}

	int startY = currentTile->getIdY() - 1;

	if (startY < 0)
	{
		startY = 0;
	}
	if (startY >= UIMANAGER->getTagMapInfoManager().Y - 3)
	{
		startY = UIMANAGER->getTagMapInfoManager().Y - 3;
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			tile* node = _vTotalList[(startY * UIMANAGER->getTagMapInfoManager().X) + startX + j + (i * UIMANAGER->getTagMapInfoManager().X)];

			//????????
			if (!node->getIsOpen()) continue;
			if (node->getAttribute() == "start") continue;
			if (node->getAttribute() == "wall") continue;

			//???? ???? ???? ??????????
			node->setParentNode(currentTile);

			reset_list.push_back((startY * UIMANAGER->getTagMapInfoManager().X) + startX + j + (i *  UIMANAGER->getTagMapInfoManager().X));

			//???? ?????? ?????????? ?????????? ?????? ???????? ?????? ???? ????
			bool addObj = true;

			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				//???? ???? ????
				if (*_viOpenList == node)
				{
					addObj = false;
					node->setIsOpen(false);
					break;
				}
			}
			//if (node->getAttribute() != "end") node->setColor(RGB(128, 64, 28));
			//???? ?????? ???? ????????
			if (!addObj) continue;

			//???? ???? ?????? ?????????? ?????? ????????
			_vOpenList.push_back(node);
		}
	}

	return _vOpenList;
}

void enemyManager::pathFinder(tile* currentTile, vector<tile*>& openlist, vector<tile*>& closeList)
{
	float tempTotalCost = 5000;
	tile* tempTile = nullptr;

	//?????????? ???? ??????, ???? ???? ?????? ????????
	for (int i = 0; i < addOpenList(currentTile, _vOpenList).size(); ++i)
	{
		//H ?? ????
		_vOpenList[i]->setCostToGoal(
			(abs(_startTile->getIdX() - _vOpenList[i]->getIdX()) +
				abs(_startTile->getIdY() - _vOpenList[i]->getIdY())) * 10);

		//
		POINT center1 = _vOpenList[i]->getParentNode()->getCenter();
		POINT center2 = _vOpenList[i]->getCenter();

		//???? ???? ?????? ?????? (?????????? 32)???? ????? ???? ??????, ?????? ????????
		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILESIZE) ? 14 : 10);

		//?? ???????? == ?? ?? ???? ???? ?? ?????? ?? ???? ??????
		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());

		//?????? ?????? ?? ???????????? ?????? ?????????? ????????,
		//???? ???? ???? ???? ????????
		if (tempTotalCost > _vOpenList[i]->getTotalCost())
		{
			tempTotalCost = _vOpenList[i]->getTotalCost();
			tempTile = _vOpenList[i];
		}

		bool addObj = true;
		for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
		{
			if (*_viOpenList == tempTile)
			{
				addObj = false;
				break;
			}
		}

		_vOpenList[i]->setIsOpen(false);

		if (!addObj) continue;

		_vOpenList.push_back(tempTile);
	}

	if (tempTile->getAttribute() == "end")
	{
		//???? ?????? ??????????
		_FindPath = true;
		while (currentTile->getParentNode() != NULL)
		{
			_vCloseList.push_back(currentTile);
			currentTile = currentTile->getParentNode();
		}
		return;
	}

	for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
	{
		//?????? ???? ?????? ?????????????? ??????????
		if (*_viOpenList == tempTile)
		{
			_viOpenList = _vOpenList.erase(_viOpenList);
			break;
		}
	}
	_currentTile = tempTile;

	pathFinder(_currentTile, _vOpenList, _vCloseList);
}

POINT enemyManager::PointMake(int x, int y)
{
	POINT temp;

	temp.x = x;
	temp.y = y;

	return temp;
}
