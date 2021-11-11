#include "stdafx.h"
#include "player.h"
#include "idleState.h"
#include "walkState.h"
#include "runState.h"
#include "attackState.h"

STATE * runState::inputHandle(player * player)
{
	if (player->getTagPlayerInfo().current_stamina <= 0) return new WalkState();

	if (KEYMANAGER->isOnceKeyUp(VK_SHIFT)) return new WalkState();

	if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::UP;
			return new runState();
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::DOWN;
			return new runState();
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT;
			return new runState();
		}
		else if (KEYMANAGER->isStayKeyDown('D'))
		{
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT;
			return new runState();
		}
		else
		{
			return new IdleState();
		}
	}

	return nullptr;
}

void runState::update(player * player)
{
	player->setTagPlayerInfo()->current_stamina -= 0.3f;

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT) {
		if (KEYMANAGER->isStayKeyDown('W')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpRun");
			player->setTagPlayer()->ani->start();
		}
		else if (KEYMANAGER->isStayKeyDown('S')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownRun");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) {
		if (KEYMANAGER->isStayKeyDown('A')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpRun");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) {
		if (KEYMANAGER->isStayKeyDown('A')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::LEFT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownRun");
			player->setTagPlayer()->ani->start();
		}
	}
	
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT) {
		if (KEYMANAGER->isStayKeyDown('W')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpRun");
			player->setTagPlayer()->ani->start();
		}
		if (KEYMANAGER->isStayKeyDown('S')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownRun");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) {
		if (KEYMANAGER->isStayKeyDown('D')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_UP;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpRun");
			player->setTagPlayer()->ani->start();
		}
	}
	else if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) {
		if (KEYMANAGER->isStayKeyDown('D')) {
			player->setTagPlayer()->dir = PLAYER_DIRECTION::RIGHT_DOWN;
			player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownRun");
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

void runState::enter(player * player)
{
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftRun");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpRun");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownRun");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightRun");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpRun");
	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownRun");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpRun");

	if (player->setTagPlayer()->dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownRun");

	player->setTagPlayer()->ani->start();

	player->setTagPlayerInfo()->speed = 5.0f;
}

void runState::exit(player * player)
{
}
