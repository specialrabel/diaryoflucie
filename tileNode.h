#pragma once
#include "stdafx.h"

#define TILESIZE 81.6

#define TILE_SCALE 1.7
#define SAMPLETILE_SCALE 0.6

//타일맵 정의
#define TILEX_ 100	//가로 타일 갯수
#define TILEY_ 100	//세로 타일 갯수

//타일셋 정의
#define SAMPLETILEX 8
#define SAMPLETILEY 16

#define ATTR_UNMOVE 0x00000001
#define ATTR_REFLECT 0x00000002
#define ATTR_SLOW 0x00000004

//지형
enum TERRAIN
{
	TR_CEMENT, TR_DESERT, TR_GRASS, TR_WATER, TR_NONE
};

//오브젝트
enum OBJECT
{
	OBJ_NOT_WALL, OBJ_WALL, OBJ_BLOCKS,
	OBJ_FLAG1, OBJ_FLAG2,
	OBJ_TANK1, OBJ_TANK2,
	OBJ_NONE
};

//포지션
enum POS
{
	POS_FLAG1, POS_FLAG2, POS_TANK1, POS_TANK2
};

enum PAGENUM
{
	PAGE1, PAGE2, PAGE3, PAGE4, PAGE5, PAGE_NUM_END
};

enum TR_PAGE
{
	PAGE1_TR, PAGE2_TR, PAGE3_TR, PAGE4_TR, PAGE5_TR, PAGE_TR_END
};

enum OBJ1_PAGE
{
	PAGE1_OBJ1, PAGE2_OBJ1, PAGE3_OBJ1, PAGE4_OBJ1, PAGE5_OBJ1, PAGE_OBJ1_END
};

enum OBJ2_PAGE
{
	PAGE1_OBJ2, PAGE2_OBJ2, PAGE3_OBJ2, PAGE4_OBJ2, PAGE5_OBJ2, PAGE_OBJ2_END
};

//타일 정보 담은 구조체
struct tagTile
{
	TERRAIN			terrain;
	OBJECT			obj;
	D2D1_RECT_F		rc;
	TR_PAGE			trPage;
	OBJ1_PAGE		objPage1;
	OBJ2_PAGE       objPage2;
	int				terrainFrameX;
	int				terrainFrameY;
	int				obj1FrameX;
	int				obj1FrameY;
	int				obj2FrameX;
	int				obj2FrameY;
};

//타일셋 정보 담을 구조체
struct tagSampleTile
{
	D2D1_RECT_F rcTile_D2D1;
	D2D1_RECT_F rcTile;
	int terrainFrameX;
	int terrainFrameY;
};

//현재 타일 받아올 구조체
struct tagCurrentTile
{
	int x;
	int y;
};

struct saveButton
{
	image* img;
	D2D1_RECT_F rc;
	int x, y;
};

struct loadButton
{
	image* img;
	D2D1_RECT_F rc;
	int x, y;
};

struct pageButton
{
	image* img;
	D2D1_RECT_F rc;
	bool push;
};