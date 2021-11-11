#pragma once
#include "gameNode.h"
#include "state.h"
#include "idleState.h"
#include "cameraState.h"
#include "bullets.h"

enum PLAYER_DIRECTION
{
	UP, LEFT_UP, LEFT, LEFT_DOWN, DOWN, RIGHT_DOWN, RIGHT, RIGHT_UP
};

enum PLAYER_EQUIP_TYPE
{
	SWORD, STAFF, ARROW
};

struct PLAYER
{
	D2D1_RECT_F rc;
	image* img;
	animation* ani;
	D2D1_MATRIX_3X2_F scale_mat;
	D2D1_MATRIX_3X2_F rotation_mat;
	Player_bullet* bullet;
	image* bullet_img;
	float bullet_scale;
	
	int player_equip_type;

	float x, y;
	float angle;
	int width, height;
	int dir;

	float gauge_count;

	bool isKeyUp;
	float keyUp_count;

	bool isMotion;

	bool left_collision, right_collision, up_collision, down_collision;
};

struct PLAYER_INFO
{
	int max_hp, max_mp, max_stamina;
	float current_hp, current_mp, current_stamina;
	float stamina_coolTime;

	float init_speed; // 스피드 초기값
	float speed;
	float run_speed;
};

struct MOUSE_POSITION
{
	float x, y;
};

class player
{
private:
	STATE* _state;

	PLAYER _player;
	PLAYER_INFO _player_info;
	MOUSE_POSITION ptMouseCursor;

	float cam_x;
	float cam_y;

	bool isMapTool;

public:

	void InputHandle();

	virtual HRESULT init(float x, float y, int dir);
	//맵툴전용
	virtual HRESULT cameraInit(int width, int height, float speed);
	virtual void release();
	virtual void update();
	virtual void render();

	inline PLAYER getTagPlayer() { return _player; }
	inline PLAYER_INFO getTagPlayerInfo() { return _player_info; }

	inline PLAYER* setTagPlayer() { return &_player; }
	inline PLAYER_INFO* setTagPlayerInfo() { return &_player_info; }
	inline STATE* setPlayerState() { return _state; }

	float getPlayerX() { return _player.x; }
	float getPlayerY() { return _player.y; }
	float setPlayerX(int playerX) { _player.x = playerX; }
	float setPlayerY(int playerY) { _player.y = playerY; }

	void setPlayerX(float speed) { _player.x += speed; }
	void setPlayerY(float speed) { _player.y += speed; }

	float getCamX() { return cam_x; }
	float getCamY() { return cam_y; }
	float getCursorX() { return ptMouseCursor.x; }
	float getCursorY() { return ptMouseCursor.y; }

	void playerInit();
};

