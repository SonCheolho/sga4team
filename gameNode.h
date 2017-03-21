#pragma once
#include "image.h"

//����� �̹����� ���������� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;			//HDC
	bool _managerInit;	//�Ŵ��� �ʱ�ȭ �߳�?

protected:
	HRESULT init(bool managerInit);

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� �̹��� ���
	image* getBackBuffer(void) { return _backBuffer; }
	//�޸�DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���(ȭ��DC)
	HDC getHDC() { return _hdc; }

	//���� ���ν���
	LRESULT CALLBACK MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode() {}
	virtual ~gameNode() {}
};

