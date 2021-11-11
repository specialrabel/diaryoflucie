#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	UIMANAGER->init();

	IMAGEMANAGER->addImage("gifTest1", L"image/title/1.gif", 1600, 900);
	gif1 = IMAGEMANAGER->findImage("gifTest1");
	IMAGEMANAGER->addImage("gifTest2", L"image/title/2.gif", 1600, 900);
	gif2 = IMAGEMANAGER->findImage("gifTest2");
	IMAGEMANAGER->addImage("gifTest3", L"image/title/3.gif", 1600, 900);
	gif3 = IMAGEMANAGER->findImage("gifTest3");

	IMAGEMANAGER->addImage("titleIMG", L"image/title/3.png", 1600, 900);
	title_IMG = IMAGEMANAGER->findImage("titleIMG");
	IMAGEMANAGER->addImage("titleTEXT", L"image/title/text.png", 917, 247);
	text_IMG = IMAGEMANAGER->findImage("titleTEXT");
	text_opacity = 0.0f;

	IMAGEMANAGER->addImage("startBtn_IMG", L"image/title/menu_button1.png", 129, 34);
	IMAGEMANAGER->addImage("maptoolBtn_IMG", L"image/title/menu_button2.png", 126, 34);
	IMAGEMANAGER->addImage("optionBtn_IMG", L"image/title/menu_button3.png", 61, 34);
	IMAGEMANAGER->addImage("exitBtn_IMG", L"image/title/menu_button4.png", 126, 34);
	menu_IMG = IMAGEMANAGER->findImage("startBtn_IMG");
	menu_move = 0;
	menu_move_dir = false;
	menu_index = 0;

	IMAGEMANAGER->addImage("leftBtn_IMG", L"image/title/left_button.png", 12, 29);
	IMAGEMANAGER->addImage("leftBtn_IMG2", L"image/title/left_button2.png", 12, 29);
	leftBtn_IMG = IMAGEMANAGER->findImage("leftBtn_IMG");
	IMAGEMANAGER->addImage("rightBtn_IMG", L"image/title/right_button.png", 12, 29);
	IMAGEMANAGER->addImage("rightBtn_IMG2", L"image/title/right_button2.png", 12, 29);
	rightBtn_IMG = IMAGEMANAGER->findImage("rightBtn_IMG");

	return S_OK;
}

void title::release()
{
}

void title::update()
{
	//로고이미지 투명도, 인트로 불값 코드
	if (gif1->getEndFrame() && gif2->getEndFrame())
	{
		text_opacity += 0.01f;

		if (text_opacity > 1.0f)
		{
			text_opacity = 1.0f;
			_isEnd_intro = true;
		}
	}

	//타이틀 인트로 gif애니메이션이 모두 재생되면, 이 if문 안쪽이 동작함.
	if (_isEnd_intro)
	{
		menu_RC = D2DMANAGER->RectMake(WINSIZEX / 2 - menu_IMG->getWidth() / 2, WINSIZEY / 2 - menu_IMG->getHeight() / 2 + 280, menu_IMG->getWidth(), menu_IMG->getHeight());
		leftBtn_RC = D2DMANAGER->RectMake(WINSIZEX / 2 - leftBtn_IMG->getWidth() / 2 - 125, WINSIZEY / 2 - leftBtn_IMG->getHeight() / 2 + 280, leftBtn_IMG->getWidth(), leftBtn_IMG->getHeight());
		rightBtn_RC = D2DMANAGER->RectMake(WINSIZEX / 2 - rightBtn_IMG->getWidth() / 2 + 125, WINSIZEY / 2 - rightBtn_IMG->getHeight() / 2 + 280, rightBtn_IMG->getWidth(), rightBtn_IMG->getHeight());

		if (PTIN_RECT(&menu_RC, _ptMouse))
		{
			if (menu_move_dir) menu_move -= 0.2f;
			else if (!menu_move_dir) menu_move += 0.2f;

			if (menu_move <= -3) menu_move_dir = false;
			else if (menu_move >= 1) menu_move_dir = true;

			menu_click_erase = true;

			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				if (menu_index == 0) SCENEMANAGER->changeScene("집");
				if (menu_index == 1) SCENEMANAGER->changeScene("맵툴");
				if (menu_index == 2);
				if (menu_index == 3) PostQuitMessage(0);
			
			}
		}
		else
		{
			if (menu_click_erase)
			{
				menu_click_erase = false;
				KEYMANAGER->release();
			}

			menu_move = 0;
			menu_move_dir = false;
		}


		leftBtn_IMG = IMAGEMANAGER->findImage("leftBtn_IMG");
		rightBtn_IMG = IMAGEMANAGER->findImage("rightBtn_IMG");

		if (PTIN_RECT(&leftBtn_RC, _ptMouse))
		{
			leftBtn_click_erase = true;

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				leftBtn_IMG = IMAGEMANAGER->findImage("leftBtn_IMG2");
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				menu_index = (MENU_MAX + menu_index - 1) % MENU_MAX;
			}
		}
		else
		{
			if (leftBtn_click_erase)
			{
				leftBtn_click_erase = false;
				KEYMANAGER->release();
			}
		}

		if (PTIN_RECT(&rightBtn_RC, _ptMouse))
		{
			rightBtn_click_erase = true;

			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				rightBtn_IMG = IMAGEMANAGER->findImage("rightBtn_IMG2");
			}
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				menu_index = (menu_index + 1) % MENU_MAX;
			}
		}
		else
		{
			if (rightBtn_click_erase)
			{
				rightBtn_click_erase = false;
				KEYMANAGER->release();
			}
		}


		if (menu_index == 0)
		{
			menu_IMG = IMAGEMANAGER->findImage("startBtn_IMG");
			menu_leftPreview_IMG = IMAGEMANAGER->findImage("exitBtn_IMG");
			menu_rightPreview_IMG = IMAGEMANAGER->findImage("maptoolBtn_IMG");
		}
		else if (menu_index == 1)
		{
			menu_IMG = IMAGEMANAGER->findImage("maptoolBtn_IMG");
			menu_leftPreview_IMG = IMAGEMANAGER->findImage("startBtn_IMG");
			menu_rightPreview_IMG = IMAGEMANAGER->findImage("optionBtn_IMG");
		}
		else if (menu_index == 2)
		{
			menu_IMG = IMAGEMANAGER->findImage("optionBtn_IMG");
			menu_leftPreview_IMG = IMAGEMANAGER->findImage("maptoolBtn_IMG");
			menu_rightPreview_IMG = IMAGEMANAGER->findImage("exitBtn_IMG");
		}
		else if (menu_index == 3)
		{
			menu_IMG = IMAGEMANAGER->findImage("exitBtn_IMG");
			menu_leftPreview_IMG = IMAGEMANAGER->findImage("optionBtn_IMG");
			menu_rightPreview_IMG = IMAGEMANAGER->findImage("startBtn_IMG");
		}

	}
	
	CAMERAMANAGER->updateScreen(0, 0);
	
}

void title::render()
{
	D2DMANAGER->pRenderTarget->Clear(ColorF(RGB(0, 0, 0)));
	
	//인트로 영상같은거
	title_IMG->render(0, 0);
	if (!gif1->getEndFrame()) gif1->gifRender(0, 0);
	if (gif1->getEndFrame() && !gif2->getEndFrame()) gif2->gifRender(0, 0);
	if (gif1->getEndFrame() && gif2->getEndFrame())
	{
		gif3->gifRender(0, 0);
		text_IMG->render(WINSIZEX / 2 - text_IMG->getWidth() / 2, WINSIZEY / 2 - text_IMG->getHeight() / 2 - 120, text_opacity);
	}

	//영상 끝나면 렌더될 것들
	if (_isEnd_intro)
	{
		menu_IMG->render(WINSIZEX / 2 - menu_IMG->getWidth() / 2, WINSIZEY / 2 - menu_IMG->getHeight() / 2 + 278 + menu_move);
		menu_leftPreview_IMG->render((WINSIZEX - 500) / 2 - menu_leftPreview_IMG->getWidth() / 2, WINSIZEY / 2 - menu_leftPreview_IMG->getHeight() / 2 + 278, 0.15f);
		menu_rightPreview_IMG->render((WINSIZEX + 500) / 2 - menu_rightPreview_IMG->getWidth() / 2, WINSIZEY / 2 - menu_rightPreview_IMG->getHeight() / 2 + 278, 0.15f);
		leftBtn_IMG->render(WINSIZEX / 2 - leftBtn_IMG->getWidth() / 2 - 125, WINSIZEY / 2 - leftBtn_IMG->getHeight() / 2 + 280);
		rightBtn_IMG->render(WINSIZEX / 2 - rightBtn_IMG->getWidth() / 2 + 125, WINSIZEY / 2 - rightBtn_IMG->getHeight() / 2 + 280);
	}

	//텍스트 (중앙 맨밑 문구)
	WCHAR str2[128];
	swprintf_s(str2, L"ver 1.0");
	D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"둥근모꼴", 17.0f, str2, WINSIZEX / 2 - 200, WINSIZEY - 20, WINSIZEX / 2 + 200, WINSIZEY);

	//D2DMANAGER->Rectangle(menu_RC);
	//D2DMANAGER->Rectangle(leftBtn_RC);
	//D2DMANAGER->Rectangle(rightBtn_RC);
}
