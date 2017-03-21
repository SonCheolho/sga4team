#include "stdafx.h"
#include "fortress.h"

HRESULT fortress::init(void)
{
	_backImg = IMAGEMANAGER->addImage("배경", "./image/fortress_background_2207_800.bmp", 2207, 800, true, RGB(255, 0, 255));
	_mapImg = IMAGEMANAGER->addImage("배경지형", "./image/fortress_background_2207_800_map.bmp", 2207, 800, true, RGB(255, 0, 255));
	_miniMapImg = IMAGEMANAGER->addImage("지형 미니맵", "./image/fortress_background_2207_800_map.bmp", 220, 80, true, RGB(255, 0, 255));

	_tankManager = new tankManager;
	_tankManager->init();

	_tankManager->addTank("문어탱", 424, 546);

	_camera.marginX = 0;
	_camera.marginY = 0;
	_camera.mapWidth = 2207;
	_camera.mapHeight = 800;
	_camera.viewWidth = WINSIZEX;
	_camera.viewHeight = WINSIZEY;
	_camera.switchViewDelay = 0;
	_camera.viewPortSetting(424, 546);
	return S_OK;
}
void fortress::release(void)
{
	_tankManager->release();
}
void fortress::update(void)
{
	_tankManager->update(&_camera);
	_camera.switchViewDelay--;
	if (_camera.switchViewDelay < 0) _camera.switchViewDelay = 0;
}
void fortress::render(void)
{
	_backImg->render(getMemDC(), _camera.marginX, _camera.marginY, _camera.viewStartX, _camera.viewStartY, _camera.viewWidth, _camera.viewHeight);
	_mapImg->render(getMemDC(), _camera.marginX, _camera.marginY, _camera.viewStartX, _camera.viewStartY, _camera.viewWidth, _camera.viewHeight);
	_tankManager->render(&_camera);
	_miniMapImg->copyAlphaRender(getMemDC(), WINSIZEX - 250, 15, _mapImg, 255);

	RECT mRc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 50, 50);
	HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
	Rectangle(getMemDC(), mRc.left, mRc.top, mRc.right, mRc.bottom);

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		RECT removeRc = RectMake(mRc.left + _camera.viewStartX, mRc.top + _camera.viewStartY, 52, 52);
		FillRect(IMAGEMANAGER->findImage("배경지형")->getMemDC(), &removeRc, hBrush);
	}
	DeleteObject(hBrush);
}