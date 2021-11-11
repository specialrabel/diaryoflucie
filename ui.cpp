#include "stdafx.h"
#include "ui.h"

HRESULT ui::init()
{
	tabMap_bool = false;

	IMAGEMANAGER->addImage("tabMap_window", L"image/tabMap/tabMap_window.png", 659, 500);
	IMAGEMANAGER->addImage("tabMap_noFind", L"image/tabMap/tabMap_noFind.png", 74, 74);
	IMAGEMANAGER->addImage("tabMap_start", L"image/tabMap/tabMap_start.png", 74, 74);
	IMAGEMANAGER->addImage("tabMap_dungeon", L"image/tabMap/tabMap_dungeon.png", 74, 74);
	IMAGEMANAGER->addImage("tabMap_bridge_width", L"image/tabMap/tabMap_bridge_width.png", 44, 20);
	IMAGEMANAGER->addImage("tabMap_bridge_height", L"image/tabMap/tabMap_bridge_height.png", 17, 44);
	IMAGEMANAGER->addImage("tabMap_current", L"image/tabMap/tabMap_current.png", 80, 80);
	IMAGEMANAGER->addImage("status_case", L"image/system/statusBar.png", 260, 83);
	IMAGEMANAGER->addImage("status_hp", L"image/system/hpBar.png", 133, 10);
	IMAGEMANAGER->addImage("status_mp", L"image/system/mpBar.png", 133, 10);
	IMAGEMANAGER->addImage("status_stamina", L"image/system/staminaBar.png", 133, 10);

	tabMap_window = IMAGEMANAGER->findImage("tabMap_window");
	tabMap_current = IMAGEMANAGER->findImage("tabMap_current");
	status_case = IMAGEMANAGER->findImage("status_case");
	status_hp = IMAGEMANAGER->findImage("status_hp");
	status_mp = IMAGEMANAGER->findImage("status_mp");
	status_stamina = IMAGEMANAGER->findImage("status_stamina");
	
	for (int i = 0; i < MAP_MAX; i++) 
	{ 
		tabMap[i].icon = IMAGEMANAGER->findImage("tabMap_noFind"); 
		tabMap[i].up = IMAGEMANAGER->findImage("tabMap_bridge_width");
		tabMap[i].down = IMAGEMANAGER->findImage("tabMap_bridge_width");
		tabMap[i].left = IMAGEMANAGER->findImage("tabMap_bridge_height");
		tabMap[i].right = IMAGEMANAGER->findImage("tabMap_bridge_height");
	}

	return S_OK;
}

void ui::release()
{
}

void ui::update()
{
	cam_x = CAMERAMANAGER->get_camera_x();
	cam_y = CAMERAMANAGER->get_camera_y();

	if (UIMANAGER->currentUI() == CURRENT_UI::PLAYING_SCREEN)
	{
		if (KEYMANAGER->isStayKeyDown(VK_TAB))
		{
			tabMap_bool = true;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_TAB))
		{
			tabMap_bool = false;
		}

		for (int i = 0; i < MAP_MAX; i++)
		{
			//통과한 맵이라면,
			if (MAPMANAGER->getTagMapInfo(i).pass)
			{
				tabMap[i].icon = IMAGEMANAGER->findImage("tabMap_dungeon");
			}
			if (MAPMANAGER->getTagMapInfo(i).type == RANDOM_MAP::START_MAP)
			{
				tabMap[i].icon = IMAGEMANAGER->findImage("tabMap_start");
			}
		}
	}

}

void ui::render()
{
	if (UIMANAGER->currentUI() == CURRENT_UI::PLAYING_SCREEN)
	{
		status_case->render(50 + cam_x, WINSIZEY - status_case->getHeight() - 50 + cam_y);
		status_hp->render(50 + cam_x + 94, WINSIZEY - status_case->getHeight() - 50 + cam_y + 11);
		status_mp->render(50 + cam_x + 94, WINSIZEY - status_case->getHeight() - 50 + cam_y + 36);
		status_stamina->renderUI(
			50 + cam_x + 94, 
			WINSIZEY - status_case->getHeight() - 50 + cam_y + 61,
			status_stamina->getWidth() - UIMANAGER->getTagPlayerInfoManager().current_stamina / UIMANAGER->getTagPlayerInfoManager().max_stamina * status_stamina->getWidth(),
			0,
			0,
			0
		);

		if (tabMap_bool)
		{
			tabMap_window->render(WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x, WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y);

			for (int i = 0; i < sqrt(MAP_MAX); i++)
			{
				for (int j = 0; j < sqrt(MAP_MAX); j++)
				{
					int x = j + i * (sqrt(MAP_MAX));

					if (MAPMANAGER->getTagMapInfo(x).pass)
					{
						tabMap[x].icon->render(WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 54 + (32 + tabMap[j].icon->getWidth()) * j, WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 42 + (40 + tabMap[i].icon->getHeight()) * i);

						if (MAPMANAGER->getTagMapInfo(x).up)
						{
							tabMap[x].up->render(
								WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 68 + (32 + tabMap[j].icon->getWidth()) * j,
								WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 22 + (40 + tabMap[i].icon->getHeight()) * i);
						}
						if (MAPMANAGER->getTagMapInfo(x).down)
						{
							tabMap[x].down->render(
								WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 68 + (32 + tabMap[j].icon->getWidth()) * j,
								WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 116 + (40 + tabMap[i].icon->getHeight()) * i);
						}
						if (MAPMANAGER->getTagMapInfo(x).left)
						{
							tabMap[x].left->render(
								WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 38 + (32 + tabMap[j].icon->getWidth()) * j,
								WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 57 + (40 + tabMap[i].icon->getHeight()) * i);
						}
						if (MAPMANAGER->getTagMapInfo(x).right)
						{
							tabMap[x].right->render(
								WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 127 + (32 + tabMap[j].icon->getWidth()) * j,
								WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 57 + (40 + tabMap[i].icon->getHeight()) * i);
						}
					}

					if (MAPMANAGER->getTagMapInfo(x).current)
					{
						tabMap_current->render(
							WINSIZEX / 2 - tabMap_window->getWidth() / 2 + cam_x + 52 + (32 + tabMap[j].icon->getWidth()) * j,
							WINSIZEY / 2 - tabMap_window->getHeight() / 2 + cam_y + 40 + (40 + tabMap[i].icon->getHeight()) * i);
					}

				}
			}
			
			WCHAR str[128];
			swprintf_s(str, L" 플레이타임");
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"The정고딕160", 20.0f, str
				, WINSIZEX / 2 + 100
				, 222
				, WINSIZEX / 2 + 405
				, 450);

			WCHAR str2[128];
			swprintf_s(str2, L"%02d : %02d", (int)TIMEMANAGER->getRecordTime() % 3600 / 60, (int)TIMEMANAGER->getRecordTime() % 60);
			D2DMANAGER->DrawTextD2DCenter(D2DMANAGER->CreateBrush(0xFFFFFF), L"The정고딕140", 20.0f, str2
				, WINSIZEX / 2 + 110
				, 262
				, WINSIZEX / 2 + 405
				, 500);
		}
	}


}
