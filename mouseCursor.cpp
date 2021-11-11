#include "stdafx.h"
#include "mouseCursor.h"

HRESULT mouseCursor::init()
{
	IMAGEMANAGER->addImage("mouseCursor1", L"image/mouseCursor/MouseCursor1.png", 32, 32);
	IMAGEMANAGER->addImage("mouseCursor1-2", L"image/mouseCursor/MouseCursor1-2.png", 32, 32);
	mouseCursor = IMAGEMANAGER->findImage("mouseCursor1");
	mouseCursor = IMAGEMANAGER->findImage("mouseCursor1-2");

	_cursorNum = basic;

	return S_OK;
}

void mouseCursor::release()
{
}

void mouseCursor::update()
{
	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();

	if (_cursorNum == basic)
	{
		mouseCursor = IMAGEMANAGER->findImage("mouseCursor1");
		if(KEYMANAGER->isStayKeyDown(VK_LBUTTON)) mouseCursor = IMAGEMANAGER->findImage("mouseCursor1-2");

		ptMouseCursor.x = _ptMouse2.x + cam_x;
		ptMouseCursor.y = _ptMouse2.y + cam_y;
	}
	else if (_cursorNum == aim)
	{

	}

}

void mouseCursor::render()
{
	D2D1_RECT_F mouseRect;

	mouseRect = D2DMANAGER->RectMake(ptMouseCursor.x, ptMouseCursor.y, 10, 10);
	//D2DMANAGER->Rectangle(mouseRect);


	if (_cursorNum == basic)
	{
		mouseCursor->render(ptMouseCursor.x - 10, ptMouseCursor.y);
	}

	/*
	//�ؽ�Ʈ
	WCHAR str2[128];
	swprintf_s(str2, L"x : %d, y : %d", ptMouseCursor.x, ptMouseCursor.y);
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"�ձٸ��", 17.0f, str2
									, ptMouseCursor.x - 350 - cam_x
									, ptMouseCursor.y - mouseCursor->getHeight() - cam_y
									, ptMouseCursor.x + 400 - cam_x
									, ptMouseCursor.y - mouseCursor->getHeight()+50 - cam_y);




	//�� �׽�Ʈ�� �ؽ�Ʈ
	WCHAR str3[128];
	swprintf_s(str3, L"%d %d %d %d \n %d %d %d %d \n %d %d %d %d \n %d %d %d %d", MAPMANAGER->getRandomMap(0),
		MAPMANAGER->getRandomMap(1),
		MAPMANAGER->getRandomMap(2),
		MAPMANAGER->getRandomMap(3),
		MAPMANAGER->getRandomMap(4),
		MAPMANAGER->getRandomMap(5),
		MAPMANAGER->getRandomMap(6),
		MAPMANAGER->getRandomMap(7),
		MAPMANAGER->getRandomMap(8),
		MAPMANAGER->getRandomMap(9),
		MAPMANAGER->getRandomMap(10),
		MAPMANAGER->getRandomMap(11),
		MAPMANAGER->getRandomMap(12),
		MAPMANAGER->getRandomMap(13),
		MAPMANAGER->getRandomMap(14),
		MAPMANAGER->getRandomMap(15));
	
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"�ձٸ��", 17.0f, str3
		, WINSIZEX / 2
		, 400
		, WINSIZEX / 2 + 1200
		, 600);

	//WCHAR str4[128];
	//swprintf_s(str4, L"���� ���ȣ : %d, ���� : %d, �Ʒ��� : %d, ���� : %d, ������ : %d",
	//	MAPMANAGER->getCurrentNum(),
	//	MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).up,
	//	MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).down,
	//	MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).left,
	//	MAPMANAGER->getTagMapInfo(MAPMANAGER->getCurrentNum()).right
	//);
	//
	//D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"�ձٸ��", 17.0f, str4
	//	, WINSIZEX / 2 - 1000
	//	, 800
	//	, WINSIZEX / 2 + 200
	//	, 1000);
	*/
}
