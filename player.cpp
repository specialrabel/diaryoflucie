#include "stdafx.h"
#include "player.h"

void player::InputHandle()
{
	STATE* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}

HRESULT player::init(float x, float y, int dir)
{
	playerInit();
	
	_player.x = x;
	_player.y = y;

	_player.dir = dir;
	
	_state = new IdleState();
	_state->enter(this);

	_player.bullet = new Player_bullet;
	_player.bullet->init(800);

	//UIMANAGER->Load(this);
	
	return S_OK;
}

HRESULT player::cameraInit(int width, int height, float speed)
{
	_player.x = width / 2;
	_player.y = height / 2;

	_player.width = width;
	_player.height = height;

	_player_info.speed = speed;

	_state = new CameraState();
	_state->enter(this);

	isMapTool = true;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();

	ptMouseCursor.x = _ptMouse2.x + cam_x;
	ptMouseCursor.y = _ptMouse2.y + cam_y;

	if (_player.x - _player.width / 2 < 0) _player.x = _player.width / 2;
	if (_player.y - _player.height / 2 < 0) _player.y = _player.height / 2;
	if (_player.x + _player.width / 2 >= CAMERAMANAGER->getMapSizeX()) _player.x = CAMERAMANAGER->getMapSizeX() - _player.width / 2;
	if (_player.y + _player.height / 2 >= CAMERAMANAGER->getMapSizeY()) _player.y = CAMERAMANAGER->getMapSizeY() - _player.height / 2;

	InputHandle();
	_state->update(this);

	if (_player.isMotion && !_player.isKeyUp)
	{
		IMAGEMANAGER->deleteImage("PLAYER_BULLET_IMG");
		_player.bullet_img = IMAGEMANAGER->addImage("PLAYER_BULLET_IMG", L"image/bullet/slime_bullet.png", _player.bullet_scale, _player.bullet_scale);
		
		_player.bullet_scale++;
	}
	if(!isMapTool) _player.bullet->update();

	//KEYANIMANAGER->update();

	_player.rc = D2DMANAGER->RectMakeCenter(_player.x, _player.y, _player.width, _player.height);
}

void player::render()
{
	//D2DMANAGER->Rectangle(_player.rc);

	_player.img->aniRender(_player.x - _player.ani->getFrameWidth() / 2, _player.y + 3 - _player.ani->getFrameHeight() / 2, _player.ani);

	//텍스트
	WCHAR str2[128];
	swprintf_s(str2, L"x : %f, y : %f 마우스 각도 %f", _player.x, _player.y, _player.angle);
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"둥근모꼴", 17.0f, str2
		, WINSIZEX / 2 - 200
		, 100
		, WINSIZEX / 2 + 200
		, 200);

	if(_player.isMotion && !_player.isKeyUp) _player.bullet_img->render(_player.x - _player.bullet_img->getWidth() / 2, (_player.y - _player.bullet_img->getHeight() / 2) - 80);
	_player.bullet->render();
}

void player::playerInit()
{
	_player.width = 50;
	_player.height = 80;

	_player_info.init_speed = 3.0f;
	_player_info.speed = 3.0f;
	_player_info.run_speed = 2.0f;

	_player_info.max_stamina = 100;
	_player_info.current_stamina = 100;

	_player.left_collision = _player.right_collision = _player.up_collision = _player.down_collision = false;

	//임시테스트
	_player.bullet_scale = 112;
	_player.player_equip_type = PLAYER_EQUIP_TYPE::STAFF;
	_player.bullet_img = IMAGEMANAGER->addImage("PLAYER_BULLET_IMG", L"image/bullet/slime_bullet.png", 32, 32);

	_player.img = IMAGEMANAGER->addFrameImage("PLAYER", L"image/player/player.png", 600 * 1.8, 7200 * 1.8, 6, 72);

	int left_idle[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftIdle", "PLAYER", left_idle, 1, 1, false);

	int left_up_idle[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpIdle", "PLAYER", left_up_idle, 1, 1, false);

	int left_down_idle[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownIdle", "PLAYER", left_down_idle, 1, 1, false);

	int right_idle[] = { 13 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightIdle", "PLAYER", right_idle, 1, 1, false);

	int right_up_idle[] = { 22 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpIdle", "PLAYER", right_up_idle, 1, 1, false);

	int right_down_idle[] = { 7 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownIdle", "PLAYER", right_down_idle, 1, 1, false);

	int up_idle[] = { 19 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpIdle", "PLAYER", up_idle, 1, 1, false);

	int down_idle[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownIdle", "PLAYER", down_idle, 1, 1, false);

	int left_walk[] = { 10, 9, 10, 11 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftWalk", "PLAYER", left_walk, 4, 7, true);

	int left_up_walk[] = { 16, 15, 16, 17 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpWalk", "PLAYER", left_up_walk, 4, 7, true);

	int left_down_walk[] = { 1, 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownWalk", "PLAYER", left_down_walk, 4, 7, true);

	int right_walk[] = { 13, 12, 13, 14 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightWalk", "PLAYER", right_walk, 4, 7, true);

	int right_up_walk[] = { 22, 21, 22, 23 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpWalk", "PLAYER", right_up_walk, 4, 7, true);

	int right_down_walk[] = { 7, 6, 7, 8 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownWalk", "PLAYER", right_down_walk, 4, 7, true);

	int up_walk[] = { 19, 18, 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpWalk", "PLAYER", up_walk, 4, 7, true);

	int down_walk[] = { 4, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownWalk", "PLAYER", down_walk, 4, 7, true);

	int left_run[] = { 175, 174, 175, 176 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftRun", "PLAYER", left_run, 4, 7, true);

	int left_up_run[] = { 204, 205, 206, 207 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpRun", "PLAYER", left_up_run, 4, 7.6f, true);

	int left_down_run[] = { 192, 193, 194, 195 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownRun", "PLAYER", left_down_run, 4, 7, true);

	int right_run[] = { 182, 183, 182, 181 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightRun", "PLAYER", right_run, 4, 7, true);

	int right_up_run[] = { 210, 211, 212, 213 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpRun", "PLAYER", right_up_run, 4, 7.6f, true);

	int right_down_run[] = { 198, 199, 200, 201 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownRun", "PLAYER", right_down_run, 4, 7, true);

	int up_run[] = { 187, 186, 187, 188 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpRun", "PLAYER", up_run, 4, 7, true);

	int down_run[] = { 169, 168, 169, 170 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownRun", "PLAYER", down_run, 4, 7, true);

	int left_attack_1[] = { 33 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttack1", "PLAYER", left_attack_1, 1, 1, true);

	int left_attack_2[] = { 34 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttack2", "PLAYER", left_attack_2, 1, 1, false);

	int left_attack_3[] = { 35 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftAttack3", "PLAYER", left_attack_3, 1, 1, false);

	int left_up_attack_1[] = { 39 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpAttack1", "PLAYER", left_up_attack_1, 1, 1, true);

	int left_up_attack_2[] = { 40 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpAttack2", "PLAYER", left_up_attack_2, 1, 1, false);

	int left_up_attack_3[] = { 41 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftUpAttack3", "PLAYER", left_up_attack_3, 1, 1, false);

	int left_down_attack_1[] = { 24 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownAttack1", "PLAYER", left_down_attack_1, 1, 1, true);

	int left_down_attack_2[] = { 25 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownAttack2", "PLAYER", left_down_attack_2, 1, 1, false);

	int left_down_attack_3[] = { 26 };
	KEYANIMANAGER->addArrayFrameAnimation("playerLeftDownAttack3", "PLAYER", left_down_attack_3, 1, 1, false);

	int right_attack_1[] = { 36 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttack1", "PLAYER", right_attack_1, 1, 1, true);

	int right_attack_2[] = { 37 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttack2", "PLAYER", right_attack_2, 1, 1, false);

	int right_attack_3[] = { 38 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightAttack3", "PLAYER", right_attack_3, 1, 1, false);

	int right_up_attack_1[] = { 45 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpAttack1", "PLAYER", right_up_attack_1, 1, 1, true);

	int right_up_attack_2[] = { 46 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpAttack2", "PLAYER", right_up_attack_2, 1, 1, false);

	int right_up_attack_3[] = { 47 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightUpAttack3", "PLAYER", right_up_attack_3, 1, 1, false);

	int right_down_attack_1[] = { 30 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownAttack1", "PLAYER", right_down_attack_1, 1, 1, true);

	int right_down_attack_2[] = { 31 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownAttack2", "PLAYER", right_down_attack_2, 1, 1, false);

	int right_down_attack_3[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("playerRightDownAttack3", "PLAYER", right_down_attack_3, 1, 1, false);

	int up_attack_1[] = { 42 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpAttack1", "PLAYER", up_attack_1, 1, 1, true);

	int up_attack_2[] = { 43 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpAttack2", "PLAYER", up_attack_2, 1, 1, false);

	int up_attack_3[] = { 44 };
	KEYANIMANAGER->addArrayFrameAnimation("playerUpAttack3", "PLAYER", up_attack_3, 1, 1, false);

	int down_attack_1[] = { 27 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownAttack1", "PLAYER", down_attack_1, 1, 1, true);

	int down_attack_2[] = { 28 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownAttack2", "PLAYER", down_attack_2, 1, 1, false);

	int down_attack_3[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDownAttack3", "PLAYER", down_attack_3, 1, 1, false);
}
