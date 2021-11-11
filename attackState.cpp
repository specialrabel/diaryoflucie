#include "stdafx.h"
#include "player.h"
#include "idleState.h"
#include "walkState.h"
#include "runState.h"
#include "attackState.h"

STATE * AttackState::inputHandle(player * player)
{
	if (!player->getTagPlayer().isMotion)
	{
		return new IdleState();
	}

	return nullptr;
}

void AttackState::update(player * player)
{
	player->setTagPlayer()->gauge_count++;

	if (player->getTagPlayer().isKeyUp) player->setTagPlayer()->keyUp_count++;

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && !player->getTagPlayer().isKeyUp)
	{
		if (player->getTagPlayer().gauge_count < 20)
		{
			if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpAttack2");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownAttack2");
		
			player->setTagPlayer()->bullet->fire(L"image/bullet/slime_bullet.png", player->getPlayerX(), player->getPlayerY()-80, player->getTagPlayer().bullet_scale, player->getTagPlayer().bullet_scale, player->getTagPlayer().angle, 4.0f);
		}
		else if (player->getTagPlayer().gauge_count >= 20)
		{
			if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpAttack3");
			else if (player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownAttack3");

			player->setTagPlayer()->bullet->fire(L"image/bullet/slime_bullet.png", player->getPlayerX(), player->getPlayerY()-80, player->getTagPlayer().bullet_scale, player->getTagPlayer().bullet_scale, player->getTagPlayer().angle, 4.0f);
		}

		player->setTagPlayer()->ani->start();

		player->setTagPlayer()->isKeyUp = true;
	}

	if (player->getTagPlayer().bullet_scale > 250)
	{
		if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpAttack3");
		else if (player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownAttack3");

		player->setTagPlayer()->bullet->fire(L"image/bullet/slime_bullet.png", player->getPlayerX(), player->getPlayerY() - 80, player->getTagPlayer().bullet_scale, player->getTagPlayer().bullet_scale, player->getTagPlayer().angle, 4.0f);
		player->setTagPlayer()->bullet_scale = 0;
		player->setTagPlayer()->isKeyUp = true;
	}

	if(player->getTagPlayer().keyUp_count >= 20) player->setTagPlayer()->isMotion = false;
}

void AttackState::enter(player * player)
{
	player->setTagPlayer()->isMotion = true;
	player->setTagPlayer()->isKeyUp = false;
	player->setTagPlayer()->gauge_count = 0;
	player->setTagPlayer()->keyUp_count = 0;
	player->setTagPlayer()->bullet_scale = 112;

	if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftUpAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::LEFT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerLeftDownAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightUpAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::RIGHT_DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerRightDownAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::UP) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerUpAttack1");
	else if (player->getTagPlayer().dir == PLAYER_DIRECTION::DOWN) player->setTagPlayer()->ani = KEYANIMANAGER->findAnimation("playerDownAttack1");

	player->setTagPlayer()->ani->start();
}

void AttackState::exit(player * player)
{
}
