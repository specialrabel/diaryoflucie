#include "stdafx.h"
#include "collisionManager.h"
#include "player.h"
//#include "bullets.h"
#include "enemyManager.h"
//#include "Object.h"
//#include "itemManager.h"

HRESULT collisionManager::init(image* stage)
{
	_stage = stage;

	//IMAGEMANAGER->addFrameImage("hit", L"image/effect/effect2.png", 1200, 100, 6, 1);

	//_hit = new effect;
	//_hit->init(IMAGEMANAGER->findImage("hit"), 200, 100, 1, 0.3f);

	return S_OK;
}

void collisionManager::release()
{
}

void collisionManager::update(int num)
{
	// 해당 충돌처리 관리를 하려면, 아래의 함수를 클릭하고 F12로 이동합시다.

	// 플레이어와 맵 충돌처리
	if (num == 0 || num == 1) pixel_collision();

	// 에너미와 맵 충돌처리
	if (num == 1) pixel_collision_enemy();

	// 플레이어 불렛과 맵 충돌처리
	//pixel_collision_bullet();

	// 플레이어와 에너미
	//player_AND_enemy();

	// 플레이어와 나뭇가지, 히든장소 문, 함정 화살충돌
	//player_AND_object();

	// 플레이어 불렛과 에너미 충돌
	//player_bullet_AND_enemy();

	// 모다피 불렛과 충돌하는것들
	//Enemy_bullet_AND_anything();

	// 아이템 충돌처리
	//item_colision();

	//아이템 줍기
	//item_pick_up();

	//적타격 이펙트
	//_hit->update();
}

void collisionManager::render()
{
	//_hit->render();
}

void collisionManager::pixel_collision()
{
	int r(0), g(0), b(0);

	for (int i = _player->getTagPlayer().rc.top; i < _player->getTagPlayer().rc.bottom; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), _player->getTagPlayer().rc.left , i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) {
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed;
			}

			break;
		}
	}

	for (int i = _player->getTagPlayer().rc.top; i < _player->getTagPlayer().rc.bottom; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), _player->getTagPlayer().rc.right, i);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed;
			}
			//if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) {
			//	_player->setTagPlayer()->left_collision = true;
			//	_player->setTagPlayer()->up_collision = true;
			//	_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
			//	_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
			//	_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
			//	_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
			//	_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
			//	_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			//}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) {
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed;
			}
		}
	}

	for (int i = _player->getTagPlayer().rc.left; i < _player->getTagPlayer().rc.right; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), i, _player->getTagPlayer().rc.top);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::UP) {
				_player->setTagPlayer()->up_collision = true;
				_player->setTagPlayer()->rc.top += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.bottom += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->y += _player->getTagPlayerInfo().speed;
			}
		}
	}

	for (int i = _player->getTagPlayer().rc.left; i < _player->getTagPlayer().rc.right; i++)
	{
		COLORREF color = GetPixel(_stage->getMemDC(), i, _player->getTagPlayer().rc.bottom);
		r = GetRValue(color);
		g = GetGValue(color);
		b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) {
				_player->setTagPlayer()->left_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x += _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed;
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) {
				_player->setTagPlayer()->right_collision = true;
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.left -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.right -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->x -= _player->getTagPlayerInfo().speed / sqrt(2);
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed / sqrt(2);
			}
			if (_player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) {
				_player->setTagPlayer()->down_collision = true;
				_player->setTagPlayer()->rc.top -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->rc.bottom -= _player->getTagPlayerInfo().speed;
				_player->setTagPlayer()->y -= _player->getTagPlayerInfo().speed;
			}
		}
	}

}

/*
void collision::pixel_collision_bullet()
{
	int r(0), g(0), b(0);

	for (int z = 0; z < _player->get_playerBullet()->get_bullet().size(); z++)
	{
		int start(0), end(0);

		D2D1_RECT_F Sheep = _player->get_playerBullet()->get_bullet()[z].rc;

		if (_player->get_playerBullet()->get_bullet()[z].type == LIGHT)
		{
			start = Sheep.bottom - 50;
			end = Sheep.bottom + 50;
		}
		else
		{
			start = Sheep.bottom - 10;
			end = Sheep.bottom + 10;
		}

		for (int i = start; i < end; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Sheep.right + Sheep.left) / 2, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_playerBullet()->set_rect(z, i);
				_player->get_playerBullet()->set_gravity(z);
				break;
			}
		}
		// 빛기둥은 측면충돌 안하니까 제외합시다
		if (_player->get_playerBullet()->get_bullet()[z].type == LIGHT) continue;

		for (int i = Sheep.left + 5; i > Sheep.left - 5; i--)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Sheep.top + Sheep.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_playerBullet()->set_direction(z, i);
				break;
			}
		}

		for (int i = Sheep.right - 5; i < Sheep.right + 5; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Sheep.top + Sheep.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_playerBullet()->set_direction(z, i);
				break;
			}
		}
	}

    //부스러기 충돌처리

	for (int z = 0; z < _player->get_fragmentBullet()->get_bullet().size(); z++)
	{
		D2D1_RECT_F Fragment = _player->get_fragmentBullet()->get_bullet()[z].rc;

		for (int i = Fragment.bottom - 20; i < Fragment.bottom + 20; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Fragment.right + Fragment.left) / 2, i);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_fragmentBullet()->set_rect(z, i);
				_player->get_fragmentBullet()->set_gravity(z);
				break;
			}
		}

		for (int i = Fragment.left + 10; i > Fragment.left - 15; i--)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, Fragment.bottom - 5);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_fragmentBullet()->set_direction(z);
				break;
			}
		}

		for (int i = Fragment.right - 10; i < Fragment.right + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, Fragment.bottom - 5);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_fragmentBullet()->set_direction(z);
				break;
			}
		}
	}

	//무기 충돌처리

	for (int z = 0; z < _player->get_WeaponBullet()->get_bullet().size(); z++)
	{
		int r_left(0), g_left(0), b_left(0);
		int r_right(0), g_right(0), b_right(0);
		float x_left(0), y_left(0), x_right(0), y_right(0);

		int direction = _player->get_WeaponBullet()->get_bullet()[z].direction;

		D2D1_RECT_F Weapon = _player->get_WeaponBullet()->get_bullet()[z].rc;

		for (int i = Weapon.bottom - 5; i < Weapon.bottom + 10; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (Weapon.right + Weapon.left) / 2, i);
			COLORREF color_left = GetPixel(_stage->getMemDC(), Weapon.left, i);
			COLORREF color_right = GetPixel(_stage->getMemDC(), Weapon.right, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			r_left = GetRValue(color_left);
			g_left = GetGValue(color_left);
			b_left = GetBValue(color_left);

			r_right = GetRValue(color_right);
			g_right = GetGValue(color_right);
			b_right = GetBValue(color_right);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);
				break;
			}

			// 지면 충돌
			if (r_left == 0 && g_left == 255 && b_left == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);

				x_left = Weapon.left;
				y_left = i;
			}

			// 지면 충돌
			if (r_right == 0 && g_right == 255 && b_right == 0)
			{
				_player->get_WeaponBullet()->set_rect(z, i);
				_player->get_WeaponBullet()->set_gravity(z);

				x_right = Weapon.right;
				y_right = i;
			}
		}

		for (int i = Weapon.left + 10; i > Weapon.left - 10; i--)
		{
			if (direction == 1) continue;
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Weapon.top + Weapon.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_WeaponBullet()->set_direction(z, i);
				_player->get_WeaponBullet()->set_speed(z);
				break;
			}
		}

		for (int i = Weapon.right - 50; i < Weapon.right + 10; i++)
		{
			if (direction == 0) continue;
			COLORREF color = GetPixel(_stage->getMemDC(), i, (Weapon.top + Weapon.bottom) / 2);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_player->get_WeaponBullet()->set_direction(z, i);
				_player->get_WeaponBullet()->set_speed(z);
				break;
			}
		}
	}
}
*/
void collisionManager::pixel_collision_enemy()
{
	int r(0), g(0), b(0);

	for (int i = 0; i < _enemy->get_enemy().size(); i++)
	{
		int direction = 0;
		bool is_triggered = false;
		D2D1_RECT_F enemy_body = _enemy->get_enemy()[i]->get_rect();

		for (int j = _enemy->get_enemy()[i]->get_rect().top; j < _enemy->get_enemy()[i]->get_rect().bottom; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _enemy->get_enemy()[i]->get_rect().left, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT);
					_enemy->get_enemy()[i]->set_left(_enemy->get_enemy()[i]->get_rect().left + _enemy->get_enemy()[i]->getSpeed());
					_enemy->get_enemy()[i]->set_x(_enemy->get_enemy()[i]->get_x() + _enemy->get_enemy()[i]->getSpeed());
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::BOTTOM);
					_enemy->get_enemy()[i]->set_left(_enemy->get_enemy()[i]->get_rect().left + _enemy->get_enemy()[i]->getSpeed() / sqrt(2));
					_enemy->get_enemy()[i]->set_top(_enemy->get_enemy()[i]->get_rect().top - _enemy->get_enemy()[i]->getSpeed() / sqrt(2));
					_enemy->get_enemy()[i]->set_x(_enemy->get_enemy()[i]->get_x() + _enemy->get_enemy()[i]->getSpeed() / sqrt(2));
					_enemy->get_enemy()[i]->set_y(_enemy->get_enemy()[i]->get_y() - _enemy->get_enemy()[i]->getSpeed() / sqrt(2));
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_BOTTOM);
				}

				break;
			}
		}

		for (int j = _enemy->get_enemy()[i]->get_rect().top; j < _enemy->get_enemy()[i]->get_rect().bottom; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), _enemy->get_enemy()[i]->get_rect().right, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::TOP);
				}
				//if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_TOP) {
				//	_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_BOTTOM);
				//}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_BOTTOM);
				}
			}
		}

		for (int j = _enemy->get_enemy()[i]->get_rect().left; j < _enemy->get_enemy()[i]->get_rect().right; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, _enemy->get_enemy()[i]->get_rect().top);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_BOTTOM);
				}
			}
		}

		for (int j = _enemy->get_enemy()[i]->get_rect().left; j < _enemy->get_enemy()[i]->get_rect().right; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), i, _enemy->get_enemy()[i]->get_rect().bottom);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 255 && g == 0 && b == 0)
			{
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_BOTTOM);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::LEFT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::RIGHT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_BOTTOM) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_TOP);
				}
				if (_enemy->get_enemy()[i]->get_direction() == enemy_direction::RIGHT_TOP) {
					_enemy->get_enemy()[i]->set_direction(enemy_direction::LEFT_BOTTOM);
				}
			}
		}
	}
}

/*
void collision::player_AND_enemy()
{
	// 플레이어 다리와 에너미 몸과 충돌했을떄, 에너미 삭제
	for (int i = 0; i < _enemy->getVMinion().size(); i++)
	{
		D2D1_RECT_F player_leg = _player->getTagPlayer()->rc;
		D2D1_RECT_F enemy_body = _enemy->getVMinion()[i]->getRect();
		// 충돌했다면
		if (INTERSECTION_RECT(temp, player_leg, enemy_body))
		{
			if (player_leg.bottom < enemy_body.top + 10)
			{
				_player->getTagPlayer()->jumpPower = 7.5f;
				_hit->startEffect(enemy_body.left, enemy_body.bottom);

				_enemy->remove_unit(i);
				break;
			}
			else if (player_leg.right > enemy_body.left + 10 && _player->getTagPlayer()->hitInterval > 120)
			{
				_player->getTagPlayer()->isHit = true;
				_player->getTagPlayer()->hitInterval = 0;

				break;
			}
			else if (player_leg.left < enemy_body.right - 10 && _player->getTagPlayer()->hitInterval > 120)
			{
				_player->getTagPlayer()->isHit = true;
				_player->getTagPlayer()->hitInterval = 0;

				break;
			}
		}

		D2D1_RECT_F player_hitBoxL = _player->getTagPlayer()->hitBoxL;
		D2D1_RECT_F player_hitBoxR = _player->getTagPlayer()->hitBoxR;

		if (INTERSECTION_RECT(temp, player_hitBoxL, enemy_body) || INTERSECTION_RECT(temp, player_hitBoxR, enemy_body))
		{
			_hit->startEffect(enemy_body.left, enemy_body.bottom);

			_enemy->remove_unit(i);
			break;
		}
	}

}

void collision::player_AND_object()
{
	// 플레이어와 나무가지 전용 충돌
	for (int i = 0; i < _obj->get_object().size(); i++)
	{
		if (_obj->get_object()[i].type != object_type::BRANCH) continue;

		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		D2D1_RECT_F Object = _obj->get_object()[i].rc;

		// 충돌했다면
		if (INTERSECTION_RECT(temp, player, Object) && !_obj->get_object()[i].is_broken)
		{
			if (player.bottom < Object.top + 10)
			{
				_obj->set_is_touched(i);

				int height = (_player->getTagPlayer()->rc.bottom - _player->getTagPlayer()->rc.top);
				_player->getTagPlayer()->rc.top = Object.top - height;
				_player->getTagPlayer()->rc.bottom = Object.top;
				_player->getTagPlayer()->y = _player->getTagPlayer()->rc.top;
				_player->getTagPlayer()->isground = true;
				_player->getTagPlayer()->isJump = false;
				_player->getTagPlayer()->jumpPower = 0;
				_player->getTagPlayer()->gravity = 0.7f;

				break;
			}
		}
	}

	// 플레이어와 히든스테이지 문과의 충돌
	for (int i = 0; i < _obj->get_object().size(); i++)
	{
		if (_obj->get_object()[i].type != object_type::GATE) continue;
		D2D1_RECT_F player = _player->getTagPlayer()->rc;
		D2D1_RECT_F Object = _obj->get_object()[i].rc;

		if (INTERSECTION_RECT(temp, player, Object))
		{
			int width = (_player->getTagPlayer()->rc.right - _player->getTagPlayer()->rc.left);
			_player->getTagPlayer()->rc.right = Object.left;
			_player->getTagPlayer()->rc.left = _player->getTagPlayer()->rc.right - width;
			_player->getTagPlayer()->x = _player->getTagPlayer()->rc.left;
			break;
		}
	}
}

void collision::player_bullet_AND_enemy()
{
	// 빛기둥과 양 충돌시 불렛 삭제
	for (int i = 0; i < _player->get_playerBullet()->get_bullet().size(); i++)
	{
		D2D1_RECT_F bullet = _player->get_playerBullet()->get_bullet()[i].rc;

		if (_player->get_playerBullet()->get_bullet()[i].type == LIGHT)
		{
			D2D1_RECT_F temp = D2DMANAGER->RectMakeCenter((bullet.left + bullet.right) / 2, (bullet.top + bullet.bottom) / 2, 40, bullet.bottom - bullet.top);
			bullet = temp;
		}

		for (int j = 0; j < _enemy->getVMinion().size(); j++)
		{
			D2D1_RECT_F enemy_body = _enemy->getVMinion()[j]->getRect();

			if (INTERSECTION_RECT(temp, bullet, enemy_body))
			{
				_enemy->remove_unit(j);
				if (_player->get_playerBullet()->get_bullet()[i].type == SHEEP)
				{
					_player->get_playerBullet()->removeMissile(i);
				}
				break;
			}
		}
	}

	// 랜스와 충돌시
	for (int i = 0; i < _player->get_WeaponBullet()->get_bullet().size(); i++)
	{
		D2D1_RECT_F Spear = _player->get_WeaponBullet()->get_bullet()[i].rc;

		for (int j = 0; j < _enemy->getVMinion().size(); j++)
		{
			D2D1_RECT_F enemy_body = _enemy->getVMinion()[j]->getRect();

			if (INTERSECTION_RECT(temp, Spear, enemy_body))
			{
				_enemy->remove_unit(j);

				if (Spear.right < enemy_body.right)
				{
					_player->get_WeaponBullet()->set_direction(i, 1);
					_player->get_WeaponBullet()->set_speed(i);
				}
				else
				{
					_player->get_WeaponBullet()->set_direction(i, 0);
					_player->get_WeaponBullet()->set_speed(i);
				}

				break;
			}
		}
	}
}

void collision::Enemy_bullet_AND_anything()
{
	int r(0), g(0), b(0);

	for (int i = 0; i < _enemy->get_bullet()->getVBullet().size(); i++)
	{
		bool is_deleted = false;

		if (_enemy->getVMinion()[i]->get_kind() != enemy_kind::PLANT) continue;

		// 플레이어 몸
		D2D1_RECT_F player_body = _player->getTagPlayer()->rc;
		// 불렛 RECT
		D2D1_RECT_F bullet = { _enemy->get_bullet()->getVBullet()[i].rc.left + 21, _enemy->get_bullet()->getVBullet()[i].rc.top,
							   _enemy->get_bullet()->getVBullet()[i].rc.right - 21, _enemy->get_bullet()->getVBullet()[i].rc.bottom };

		// 플레이어와 모다피 불렛이 충돌시 총알삭제 -> 추후 이펙트와 플레이어 죽는 모습 넣어야함

		if (INTERSECTION_RECT(temp, player_body, bullet))
		{
			_enemy->get_bullet()->removeBullet(i);
			is_deleted = true;
			break;
		}

		if (is_deleted)
		{
			break;
		}

		// 불렛과 지면 충돌시 불렛 삭제
		for (int j = bullet.bottom - 5; j < bullet.bottom + 5; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (bullet.left + bullet.right) / 2, j);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 0)
			{
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}

		// 불렛과 측면 충돌시 불렛삭제 (왼쪽)
		for (int j = bullet.left - 10; j < bullet.left + 10; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (bullet.top + bullet.bottom) / 2);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 255)
			{
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}
		// 불렛과 측면 충돌시 불렛삭제 (오른쪽)
		for (int j = bullet.right - 10; j < bullet.right + 10; j++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), j, (bullet.top + bullet.bottom) / 2);
			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			// 지면 충돌
			if (r == 0 && g == 255 && b == 255)
			{
				_enemy->get_bullet()->removeBullet(i);
				is_deleted = true;
				break;
			}
		}
		if (is_deleted)
		{
			break;
		}
	}

}

void collision::item_colision()
{
	int r(0), g(0), b(0);
	for (int j = 0; j < _im->getvWeapon().size(); j++)
	{
		D2D1_RECT_F item = _im->getvWeapon()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvWeapon()[j].typeNum, j, i);
				break;
			}
		}
	}

	for (int j = 0; j < _im->getvArmor().size(); j++)
	{
		D2D1_RECT_F item = _im->getvArmor()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvArmor()[j].typeNum, j, i);
				break;
			}
		}
	}

	for (int j = 0; j < _im->getvOther().size(); j++)
	{
		D2D1_RECT_F item = _im->getvOther()[j].rc;
		for (int i = item.bottom - 15; i < item.bottom + 15; i++)
		{
			COLORREF color = GetPixel(_stage->getMemDC(), (item.right + item.left) / 2, i);

			r = GetRValue(color);
			g = GetGValue(color);
			b = GetBValue(color);

			if (r == 0 && g == 255 && b == 0)
			{
				_im->setGravity(_im->getvOther()[j].typeNum, j, i);
				break;
			}
		}
	}

}


void collision::bird_AND_enemy()
{
	//새 총알 개수 20개
	for (int m = 0; m < 20; m++)
	{
		//새 총알이 발사되어 있다면
		if (_bird->getRcBirdShot(m))
		{
			//생성되있는 적들과 충돌 확인
			for (int i = 0; i < _enemy->getVMinion().size(); i++)
			{
				D2D1_RECT_F bird = _bird->getBirdRC(m);
				D2D1_RECT_F enemy_body = _enemy->getVMinion()[i]->getRect();

				// 충돌했다면
				if (INTERSECTION_RECT(temp, bird, enemy_body))
				{
					_bird->setBirdDistory(m);
					_enemy->remove_unit(i);
					break;

				}
			}


		}
	}

}


//void collision::item_pick_up()
//{
//
//	if (_player->getPickUpCheck())
//	{
//		//동작하면 신호 꺼주기
//		_player->setPickUpCheckF();
//
//		//방어구 추가해야함
//		D2D1_RECT_F player = _player->getTagPlayer()->rc;
//
//		for (int j = 0; j < _im->getvWeapon().size(); j++)
//		{
//			D2D1_RECT_F item = _im->getvWeapon()[j].rc;
//
//			if (INTERSECTION_RECT(temp, player, item))
//			{
//				int type = _im->getItemType(j);
//				int color = _im->getItemColor(j);
//				int durability = _im->getItemDurability(j);
//				//인벤토리를 확인하고 주울 수 있으면 아이템 삭제 못주우면 방치
//				if (_player->pickUpItem(type, color, durability))
//				{
//					_im->removeItem(j);
//				}
//			}
//		}
//	}
//}

*/