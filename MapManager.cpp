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
// 16���� �迭�� ����, ����1, ����2, ���� ��Ÿ���� type�� �����ϰ� ��������.
// 16���� �迭�� ���� ��ġ���� �̵��� �� �ִ� ������ ��������.
//====================================================================== 

void MapManager::randomMap()
{
	int start_num;	// �������� ���ϱ�
	int end_num;	// �������� ���ϱ�
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

	int dungeon_max = 2; // ������ ���� ����
	int dungeon_num; // ������ ���� ������

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

										//�Ʒ��� �̵��� ������ �ʵ�
		if (i < MAP_MAX - SQRT)			_random_map[i].down = true;

										//���� �̵��� ������ �ʵ�
		if (i >= SQRT)					_random_map[i].up = true;

										//������ �̵��� ������ �ʵ�
		if ((i + 1) % SQRT != 0)		_random_map[i].right = true;

										//���� �̵��� ������ �ʵ�
		if (i % SQRT != 0)				_random_map[i].left = true;
	}

	for (int i = 0; i < MAP_MAX; i++)
	{
		for (int j = 0; j < MAP_MAX; j++)
		{
			//����
			if (_random_map[i].type == RANDOM_MAP::START_MAP && _random_map[j].type == RANDOM_MAP::END_MAP)
			{
				//������ ���� �¿� �ִܰ�� ���� (ex. 0��° ĭ start, 2��° ĭ end)
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

				//������ ���� ���� �ִܰ�� ���� 1
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

				//������ ���� ���� �ִܰ�� ���� 2
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

	//4���� �� �������� ���
	for (int i = 0; i < MAP_MAX; i++)
	{
		if (!_random_map[i].up && !_random_map[i].down && !_random_map[i].left && !_random_map[i].right)
		{	
			//�𼭸� �κ��̶��
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
// ������ ��ġ�� �迭 current �Ұ��� true�� �ٲ������ν�,
// ������ ��ġ�� �������� �� ����.
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
// ���� ��ġ�� �ִ� �迭�� ���ڸ� �˾Ƴ���,
// ��� ���� current �Ұ��� false�� �ٲ� ��,
// ���� �̵��� ���⿡ ���� �ش� �迭�� current �Ұ��� true�� �ٲ������ν� ���� ��ġ�� ������.
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
//���� �� ��ȣ�� �� �� �ִ� �Լ�
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