#include "stdafx.h"
#include "gameNode.h"


gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		TIMEMANAGER->init();
		EFFECTMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		TXTDATA->init();
		INIDATA->init();
		D2DMANAGER->Init();
		IMAGEMANAGER->init();
		KEYANIMANAGER->init();
		CAMERAMANAGER->init(MAPSIZEX, MAPSIZEY);
		MAPMANAGER->init();
		UIMANAGER->init();
		ITEMMANAGER->init();
	}

	return S_OK;
}

void gameNode::release()
{
	if (_managerInit)
	{
		KillTimer(_hWnd, 1);
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();

		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();

		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();

		TXTDATA->release();
		TXTDATA->releaseSingleton();

		INIDATA->release();
		INIDATA->releaseSingleton();

		D2DMANAGER->release();
		D2DMANAGER->releaseSingleton();

		KEYANIMANAGER->release();
		KEYANIMANAGER->releaseSingleton();

		CAMERAMANAGER->release();
		CAMERAMANAGER->releaseSingleton();

		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		MAPMANAGER->release();
		MAPMANAGER->releaseSingleton();

		UIMANAGER->release();
		UIMANAGER->releaseSingleton();

		ITEMMANAGER->release();
		ITEMMANAGER->releaseSingleton();
	}
	
	ReleaseDC(_hWnd, _hdc);
}

void gameNode::update()
{
	
}

void gameNode::render()
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //�� �� �߿��մ�...
	static CHAR str[MAX_PATH];
	int nlen = 0;

	switch (iMessage)
	{
		
		//���콺 �����̸� ���⼭ �޼��� �߻�
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam)) + CAMERAMANAGER->get_camera_x();
			_ptMouse.y = static_cast<float>(HIWORD(lParam)) + CAMERAMANAGER->get_camera_y();

			_ptMouse2.x = static_cast<float>(LOWORD(lParam));
			_ptMouse2.y = static_cast<float>(HIWORD(lParam));

		break;
			//���콺 ���� Ŭ��(�������� ������ ����)

		//case WM_KEYDOWN:

		//	switch (wParam)
		//	{
		//		case VK_ESCAPE:
		//			PostQuitMessage(0);
		//			break;
		//	}
		//	break;

		case WM_CHAR:
			nlen = strlen((char *)str);
			str[nlen] = (char)wParam;
			str[nlen + 1] = 0;
			_char[nlen] = (char)wParam;

			//�齺���̽� ������ ������ ���� ��������
			if ((char)wParam == VK_BACK && nlen > 0)
			{
				str[nlen - 1] = 0;
				_char[nlen - 1] = 0;
			}
					
			////���͸� ������ ���ڿ� �ʱ�ȭ
			//if ((char)wParam == VK_LBUTTON) {
			//	for (int i = 0; i < nlen; i++)
			//	{
			//		str[i] = 0;
			//		_char[i] = 0;
			//	}
			//}

			if (nlen > 3)
			{
				for (int i = 0; i < nlen; i++)
				{
					str[i] = 0;
					_char[i] = 0;
				}
			}

		break;
		
		
		//������ â �ν���(?) 
		case WM_DESTROY:
		//������ �����Լ�
			PostQuitMessage(0);
			CoUninitialize();
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}
