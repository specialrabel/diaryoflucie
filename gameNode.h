#pragma once
#include "image.h"

enum CTRL
{
	CTRL_SAVE,			//세이브		버튼
	CTRL_LOAD,			//로드		버튼
	CTRL_TERRAINDRAW,	//지형		버튼
	CTRL_OBJDRAW1,		//오브젝트	버튼
	CTRL_OBJDRAW2,		//오브젝트	버튼
	CTRL_ERASER,		//지우개		버튼
	CTRL_END
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	
public:
	gameNode();
	virtual ~gameNode();

	int _ctrSelect;

	//HRESULT 마소 전용 반환형식인데
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release();			//메모리 해제 함수
	virtual void update();			//연산 함수
	virtual void render();	//그리기 함수

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

