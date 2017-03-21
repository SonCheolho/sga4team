#include "stdafx.h"
#include "pixelCollision.h"

HRESULT pixelCollision::init(void)
{
	//백그라운드 이미지 
	_mountain = IMAGEMANAGER->addImage("mountain", "mountain.bmp", 800, 600, true, RGB(255, 0, 255));

	//공이미지
	_ball = IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//공위치 초기화
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());

	//Y축으로 탐지(공의 하단에 사각형 만들기)
	_probeY = _y + _ball->getHeight() / 2;

	return S_OK;
}

void pixelCollision::release(void)
{
}

void pixelCollision::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 3.0f;
	}
	//공의 렉트도 같이 움직이기
	_rc = RectMakeCenter(_x, _y, _ball->getWidth(), _ball->getHeight());
	//Y축으로 탐지(공의 하단에 사각형 만들기)
	_probeY = _y + _ball->getHeight() / 2;

	/*이부분이 픽셀충돌 핵심*/
	//탐지할 Y값의 범위를 위아래로 원하는 만큼 검사를 한다
	for (int i = _probeY - 20; i < _probeY + 20; i++)
	{
		COLORREF color = GetPixel(_mountain->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _ball->getHeight() / 2;
			break;
		}
	}
}

void pixelCollision::render(void)
{
	//백그라운드 이미지 렌더
	_mountain->render(getMemDC());
	//공이미지 렌더
	_ball->render(getMemDC(), _rc.left, _rc.top);
}
