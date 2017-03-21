#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}

mainGame::~mainGame()
{
}

//============================================================================
//		## 초기화 ## init(void)
//============================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	//이곳에서 초기화를 한다.

	_megamanX6 = new megamanX6();
	_megamanX6->init();

	_fortress = new fortress;
	_fortress->init();
	return S_OK;
}
//============================================================================
//		## 해제 ## release(void)
//============================================================================
void mainGame::release(void)
{
	gameNode::release();
	//이미지 클래스 나갈때까진 사용할 일 없다.

	_megamanX6->release();
	SAFE_DELETE(_megamanX6);
	_fortress->release();
	SAFE_DELETE(_fortress);
}
//============================================================================
//		## 업데이트 ## update(void)
//============================================================================
void mainGame::update(void)
{
	gameNode::update();

	//이곳에서 계산식, 키보드, 마우스 등등 업데이트 한다.
	if(KEYMANAGER->isToggleKey('1')) _megamanX6->update();
	else if (KEYMANAGER->isToggleKey('2')) _fortress->update();
}
//============================================================================
//		## 렌더 ## render(HDC hdc)
//============================================================================
void mainGame::render(void)
{
	/*이미지 매니져 사용시*/
	//힌색 빈 비트맵 (이것도 렌더에 그냥 그대로 둘것!!);
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//이곳에서 WM_PAINT에서 햇던것을 처리하면 된다.
//============================================================================
	
	//이곳에서 이후 이미지 처리
	if (KEYMANAGER->isToggleKey('1')) _megamanX6->render(getMemDC());
	else if (KEYMANAGER->isToggleKey('2')) _fortress->render();

//============================================================================
	//백버퍼의 내용을 HDC에 드린다(이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}

//============================================================================
//		## 일반 함수 ## (너희들이 만든함수)
//============================================================================
