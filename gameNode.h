#pragma once
#include "image.h"

//백버퍼 이미지를 스태틱으로 만들어 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//매니져 초기화 했냐?

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//백버퍼 얻어오기
	image* getBackBuffer(void) { return _backBuffer; }
	//메모리DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기
	HDC getHDC() { return _hdc; }

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode();
	virtual ~gameNode();
};