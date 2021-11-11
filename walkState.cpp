#include "stdafx.h"
#include "player.h"
#include "idleState.h"
#include "walkState.h"
#include "runState.h"
#include "attackState.h"

STATE * WalkState::inputHandle(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_SHIFT) && player->getTagPlayerInfo().current_stamina > 0) return new runState();

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_UP)
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('W'))
			return new IdleState();
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_DOWN)
	{
		if (KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('S'))
			return new IdleState();
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_UP)
	{
		if (KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('W'))
			return new IdleState();
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_DOWN)
	{
		if (KEYMANAGER->isOnceKeyUp('D') || KEYMANAGER->isOnceKeyUp('S'))
			return new IdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('A')) {
		return new IdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('D')) {
		return new IdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('W')) {
		return new IdleState();
	}
	if (KEYMANAGER->isOnceKeyUp('S')) {
		return new IdleState();
	}

	return nullptr;
}

void WalkState::update(player * player)
{
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT) {
		if (KEYMANAGER->isStayKeyDown('W')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpWalk");
			player->setTagPlayer()->ani->start();
		}
		else if (KEYMANAGER->isStayKeyDown('S')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownWalk");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) {
		if (KEYMANAGER->isStayKeyDown('A')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpWalk");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) {
		if (KEYMANAGER->isStayKeyDown('A')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownWalk");
			player->setTagPlayer()->ani->start();
		}
	}

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT) {
		if (KEYMANAGER->isStayKeyDown('W')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpWalk");
			player->setTagPlayer()->ani->start();
		}
		if (KEYMANAGER->isStayKeyDown('S')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownWalk");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) {
		if (KEYMANAGER->isStayKeyDown('D')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpWalk");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) {
		if (KEYMANAGER->isStayKeyDown('D')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownWalk");
			player->setTagPlayer()->ani->start();
		}
	}


	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT && !player->getTagPlayer().left_collision) {
		player->setTagPlayer()->x -= player->getTagPlayerInfo().speed;
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT && !player->getTagPlayer().right_collision) {
		player->setTagPlayer()->x += player->getTagPlayerInfo().speed;
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP && !player->getTagPlayer().up_collision) {
		player->setTagPlayer()->y -= player->getTagPlayerInfo().speed;
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN && !player->getTagPlayer().down_collision) {
		player->setTagPlayer()->y += player->getTagPlayerInfo().speed;
	}

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_UP) {
		player->setTagPlayer()->x -= player->getTagPlayerInfo().speed / sqrt(2);
		player->setTagPlayer()->y -= player->getTagPlayerInfo().speed / sqrt(2);
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_DOWN) {
		player->setTagPlayer()->x -= player->getTagPlayerInfo().speed / sqrt(2);
		player->setTagPlayer()->y += player->getTagPlayerInfo().speed / sqrt(2);
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_UP) {
		player->setTagPlayer()->x += player->getTagPlayerInfo().speed / sqrt(2);
		player->setTagPlayer()->y -= player->getTagPlayerInfo().speed / sqrt(2);
	}
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_DOWN) {
		player->setTagPlayer()->x += player->getTagPlayerInfo().speed / sqrt(2);
		player->setTagPlayer()->y += player->getTagPlayerInfo().speed / sqrt(2);
	}

	if (KEYMANAGER->isStayKeyDown('A')) {
		player->setTagPlayer()->left_collision = false;
		player->setTagPlayer()->right_collision = false;
		player->setTagPlayer()->up_collision = false;
		player->setTagPlayer()->down_collision = false;
	}
	if (KEYMANAGER->isStayKeyDown('D')) {
		player->setTagPlayer()->left_collision = false;
		player->setTagPlayer()->right_collision = false;
		player->setTagPlayer()->up_collision = false;
		player->setTagPlayer()->down_collision = false;
	}
	if (KEYMANAGER->isStayKeyDown('W')) {
		player->setTagPlayer()->left_collision = false;
		player->setTagPlayer()->right_collision = false;
		player->setTagPlayer()->up_collision = false;
		player->setTagPlayer()->down_collision = false;
	}
	if (KEYMANAGER->isStayKeyDown('S')) {
		player->setTagPlayer()->left_collision = false;
		player->setTagPlayer()->right_collision = false;
		player->setTagPlayer()->up_collision = false;
		player->setTagPlayer()->down_collision = false;
	}
}

void WalkState::enter(player * player)
{
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftWalk");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpWalk");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownWalk");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightWalk");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpWalk");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownWalk");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpWalk");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownWalk");

	player->setTagPlayer()->ani->start();

	player->setTagPlayerInfo()->speed = 3.0f;
}

void WalkState::exit(player * player)
{

}