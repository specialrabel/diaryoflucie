#include "stdafx.h"
#include "player.h"
#include "idleState.h"
#include "walkState.h"
#include "runState.h"
#include "attackState.h"

STATE * IdleState::inputHandle(player * player)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		player->setTagPlayer()->angle = getAngle(player->getTagPlayer().x, player->getTagPlayer().y, player->getCursorX(), player->getCursorY());

		if (player->getTagPlayer().angle >= PI2) player->setTagPlayer()->angle -= PI2;
		if (player->getTagPlayer().angle <= 0) player->setTagPlayer()->angle += PI2;

		if (player->getTagPlayer().angle > 0 && player->setTagPlayer()->angle <= PI8 || player->setTagPlayer()->angle > 15 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT;
		}
		else if (player->getTagPlayer().angle > PI8 && player->getTagPlayer().angle <= 3 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_UP;
		}
		else if (player->getTagPlayer().angle > 3 * PI8 && player->getTagPlayer().angle <= 5 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::UP;
		}
		else if (player->getTagPlayer().angle > 5 * PI8 && player->getTagPlayer().angle <= 7 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_UP;
		}
		else if (player->getTagPlayer().angle > 7 * PI8 && player->getTagPlayer().angle <= 9 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT;
		}
		else if (player->getTagPlayer().angle > 9 * PI8 && player->getTagPlayer().angle <= 11 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_DOWN;
		}
		else if (player->getTagPlayer().angle > 11 * PI8 && player->getTagPlayer().angle <= 13 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::DOWN;
		}
		else if (player->getTagPlayer().angle > 13 * PI8 && player->getTagPlayer().angle <= 15 * PI8)
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_DOWN;
		}

		return new AttackState();
	}

	if (KEYMANAGER->isStayKeyDown('A'))
	{
		player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT;
		
		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && player->getTagPlayerInfo().current_stamina > 0) return new runState();

		return new WalkState();
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT;

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && player->getTagPlayerInfo().current_stamina > 0) return new runState();

		return new WalkState();
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		player->setTagPlayer()->dir = PLAYER_DIRECTION::UP;

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && player->getTagPlayerInfo().current_stamina > 0) return new runState();

		return new WalkState();
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		player->setTagPlayer()->dir = PLAYER_DIRECTION::DOWN;

		if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && player->getTagPlayerInfo().current_stamina > 0) return new runState();

		return new WalkState();
	}

	return nullptr;
}

void IdleState::update(player * player)
{
	player->setTagPlayerInfo()->stamina_coolTime += 1;

	if (player->getTagPlayerInfo().stamina_coolTime > 10 && player->getTagPlayerInfo().current_stamina <= 100) player->setTagPlayerInfo()->current_stamina += 0.8f;
} 

void IdleState::enter(player * player)
{
	player->setTagPlayerInfo()->stamina_coolTime = 0;

	if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::UP) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpIdle");
	}
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) {
		player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownIdle");
	}

	player->setTagPlayer()->ani->start();

	player->setTagPlayerInfo()->speed = 3.0f;
}

void IdleState::exit(player * player)
{

}
