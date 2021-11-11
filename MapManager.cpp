#include "stdafx.h"
#include "MapManager.h"

HRESULT MapManager::init()
{
	_direction = MOVE_MAP::MAP_START;

	randomMap();

	return S_OK;
}

void MapManager::release()
{
}

//======================================================================
// 16개의 배열에 시작, 던전1, 던전2, 끝을 나타내는 type을 랜덤하게 지정해줌.
// 16개의 배열에 각자 위치에서 이동할 수 있는 방향을 지정해줌.
//====================================================================== 

void MapManager::randomMap()
{
	int start_num;	// 시작지점 정하기
	int end_num;	// 도착지점 정하기
	int SQRT = sqrt(MAP_MAX);

	for (int i = 0; i < 1000000; i++)
	{
		start_num = RND->getInt(MAP_MAX);
		end_num = RND->getInt(MAP_MAX);

		if (start_num != end_num)
		{
			if (start_num != end_num + (SQRT + 1) && start_num != end_num + (SQRT + 0) && start_num != end_num + (SQRT - 1)
				&& start_num != end_num + 1 && start_num != end_num - 1
				&& start_num != end_num - (SQRT - 1) && start_num != end_num - (SQRT - 0) && start_num != end_num - (SQRT + 1))
			{
				_random_map[start_num].type = RANDOM_MAP::START_MAP;
				_random_map[end_num].type = RANDOM_MAP::END_MAP;

				break;
			}
		}
	}

	int dungeon_max = 2; // 던전맵 종류 갯수
	int dungeon_num; // 던전맵 랜덤 돌리기

	for (int i = 0; i < MAP_MAX; i++)
	{
		dungeon_num = RND->getInt(dungeon_max) + 1;

		if (i != start_num && i != end_num) {
			_random_map[i].type = dungeon_num;
		}
	}


	for (int i = 0; i < MAP_MAX; i++)
	{
		_random_map[i].up = _random_map[i].down = _random_map[i].right = _random_map[i].left = false;

										//아래쪽 이동이 가능한 맵들
		if (i < MAP_MAX - SQRT)			_random_map[i].down = true;

										//위쪽 이동이 가능한 맵들
		if (i >= SQRT)					_random_map[i].up = true;

										//오른쪽 이동이 가능한 맵들
		if ((i + 1) % SQRT != 0)		_random_map[i].right = true;

										//왼쪽 이동이 가능한 맵들
		if (i % SQRT != 0)				_random_map[i].left = true;
	}

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			//시작
			if (_random_map[i].type == RANDOM_MAP::START_MAP && _random_map[j].type == RANDOM_MAP::END_MAP)
			{
				//시작점 끝점 좌우 최단경로 방지 (ex. 0번째 칸 start, 2번째 칸 end)
				if (0 <= i < SQRT*3 && 0 <= j < SQRT*3 || SQRT <= i < SQRT*4 && SQRT <= j < SQRT*4)
				{
					if (i % SQRT < j % SQRT) 
					{
						_random_map[i].right = false;
						if(i < MAP_MAX) _random_map[i + 1].left = false;
						_random_map[j].left = false;
						if(j > 0) _random_map[j - 1].right = false;
					}
					else if (i % SQRT > j % SQRT)
					{
						_random_map[i].left = false;
						if(i > 0) _random_map[i - 1].right = false;
						_random_map[j].right = false;
						if(j < MAP_MAX) _random_map[j + 1].left = false;
					}
				}

				//시작점 끝점 상하 최단경로 방지 1
				if (i != (SQRT - 1) && i != (SQRT*2 - 1) && i != (SQRT*3 - 1) && i != (SQRT*4 - 1))
				{
					if (j != (SQRT - 1) && j != (SQRT * 2 - 1) && j != (SQRT * 3 - 1) && j != (SQRT * 4 - 1))
					{
						if (i < j)
						{
							_random_map[i].down = false;
							if(i < SQRT*SQRT-SQRT) _random_map[i + SQRT].up = false;
							_random_map[j].up = false;
							if(j >= SQRT) _random_map[j - SQRT].down = false;
						}
						else if (j < i)
						{
							_random_map[i].up = false;
							if (i >= SQRT) _random_map[i - SQRT].down = false;
							_random_map[j].down = false;
							if (j < SQRT*SQRT - SQRT) _random_map[j + SQRT].up = false;
						}
					}
				}

				//시작점 끝점 상하 최단경로 방지 2
				if (i != SQRT*0 && i != SQRT*1 && i != SQRT*2 && i != SQRT * 3)
				{
					if (j != SQRT * 0 && j != SQRT * 1 && j != SQRT * 2 && j != SQRT * 3)
					{
						if (i < j)
						{
							_random_map[i].down = false;
							if (i < SQRT*SQRT - SQRT) _random_map[i + SQRT].up = false;
							_random_map[j].up = false;
							if (j >= SQRT) _random_map[j - SQRT].down = false;
						}
						else if (j < i)
						{
							_random_map[i].up = false;
							if (i >= SQRT) _random_map[i - SQRT].down = false;
							_random_map[j].down = false;
							if (j < SQRT*SQRT - SQRT) _random_map[j + SQRT].up = false;
						}
					}
				}
			}
		}
	}

	//4방향 다 막혀있을 경우
	for (int i = 0; i < MAP_MAX; i++)
	{
		if (!_random_map[i].up && !_random_map[i].down && !_random_map[i].left && !_random_map[i].right)
		{	
			//모서리 부분이라면
			if (i == 0 || i == SQRT - 1 || i == SQRT * SQRT - SQRT || i == SQRT * SQRT - 1)
			{
				if (i < MAP_MAX - SQRT)
				{
					_random_map[i].down = true;
					_random_map[i + SQRT].up = true;
				}

				if (i >= SQRT)
				{
					_random_map[i].up = true;
					_random_map[i - SQRT].down = true;
				}

				if ((i + 1) % SQRT != 0)
				{
					_random_map[i].right = true;
					_random_map[i + 1].left = true;
				}

				if (i % SQRT != 0)
				{
					_random_map[i].left = true;
					_random_map[i - 1].right = true;
				}
			}
		}
	}

	for (int i = 0; i < MAP_MAX; i++)
	{
		_random_map[i].pass = false;
	}
}

//==============================================================
// 시작한 위치의 배열 current 불값을 true로 바꿔줌으로써,
// 시작한 위치를 지정받을 수 있음.
//============================================================== 

void MapManager::startMap()
{
	for (int i = 0; i < MAP_MAX; i++)
	{
		_random_map[i].current = false;
	
		if (_random_map[i].type == RANDOM_MAP::START_MAP) {
			
			_random_map[i].current = true;
			_random_map[i].pass = true;
		}
	}
}

//==============================================================
// 현재 위치해 있던 배열의 숫자를 알아내고,
// 모든 맵의 current 불값을 false로 바꾼 뒤,
// 맵을 이동한 방향에 따라 해당 배열의 current 불값을 true로 바꿔줌으로써 현재 위치를 지정함.
//============================================================== 

void MapManager::moveMap(int dir)
{
	int num;

	for (int i = 0; i < MAP_MAX; i++)
	{
		if (_random_map[i].current == true)
		{
			num = i;
		}

		_random_map[i].current = false;

	}

	if (dir == MOVE_MAP::MAP_UP)
	{
		_random_map[num - 4].current = true;
		_random_map[num - 4].pass = true;
		_direction = MOVE_MAP::MAP_UP;
	}

	else if (dir == MOVE_MAP::MAP_DOWN)
	{
		_random_map[num + 4].current = true;
		_random_map[num + 4].pass = true;
		_direction = MOVE_MAP::MAP_DOWN;
	}

	else if (dir == MOVE_MAP::MAP_LEFT)
	{
		_random_map[num - 1].current = true;
		_random_map[num - 1].pass = true;
		_direction = MOVE_MAP::MAP_LEFT;
	}

	else if (dir == MOVE_MAP::MAP_RIGHT)
	{
		_random_map[num + 1].current = true;
		_random_map[num + 1].pass = true;
		_direction = MOVE_MAP::MAP_RIGHT;
	}

}

//============================
//현재 맵 번호를 알 수 있는 함수
//============================
int MapManager::getCurrentNum()
{
	int currentNum;

	for (int i = 0; i < MAP_MAX; i++)
	{
		if (_random_map[i].current) { currentNum = i; }
	}

	return currentNum;
}