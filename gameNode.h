#pragma once
#include "image.h"

enum CTRL
{
	CTRL_SAVE,			//���̺�		��ư
	CTRL_LOAD,			//�ε�		��ư
	CTRL_TERRAINDRAW,	//����		��ư
	CTRL_OBJDRAW1,		//������Ʈ	��ư
	CTRL_OBJDRAW2,		//������Ʈ	��ư
	CTRL_ERASER,		//���찳		��ư
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

	//HRESULT ���� ���� ��ȯ�����ε�
	//S_OK, E_FAIL, SUCCEDED
	virtual HRESULT init();			//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();			//�޸� ���� �Լ�
	virtual void update();			//���� �Լ�
	virtual void render();	//�׸��� �Լ�

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

