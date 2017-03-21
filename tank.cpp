#include "stdafx.h"
#include "tank.h"

HRESULT tankManager::init(void)
{
	IMAGEMANAGER->addFrameImage("문어탱 - 대기", "./image/fortress_nomal_1508_146.bmp", 1508, 146, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("문어탱 - 공격준비", "./image/fortress_shoot_ready_464_146.bmp", 464, 146, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("문어탱 - 공격", "./image/fortress_shoot_812_146.bmp", 812, 146, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("문어탱 - 공격탄환", "./image/bullet_type2_256_16.bmp", 256, 16, 16, 1, true, RGB(255, 0, 255));
	_bullet = new parabolaBullet;
	_bullet->init();
	return S_OK;
}
void tankManager::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_vTank.clear();
}
void tankManager::update(LPCAMERA camera)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (!_viTank->isLeft)
			{
				_viTank->isLeft = true;
				_viTank->cannonAngle = PI - _viTank->cannonAngle;
				_viTank->cannonMaxAngle = PI - _viTank->cannonMaxAngle;
				_viTank->cannonMinAngle = PI - _viTank->cannonMinAngle;
				_viTank->tankAngle = PI + _viTank->tankAngle;
			}
			_viTank->x -= 1.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (_viTank->isLeft)
			{
				_viTank->isLeft = false;
				_viTank->cannonAngle = PI - _viTank->cannonAngle;
				_viTank->cannonMaxAngle = PI - _viTank->cannonMaxAngle;
				_viTank->cannonMinAngle = PI - _viTank->cannonMinAngle;
				_viTank->tankAngle = _viTank->tankAngle - PI;
			}
			_viTank->x += 1.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (_viTank->isLeft)
			{
				_viTank->cannonAngle -= 0.01f;
				if (_viTank->cannonAngle < _viTank->cannonMaxAngle) _viTank->cannonAngle = _viTank->cannonMaxAngle;
			}
			else
			{
				_viTank->cannonAngle += 0.01f;
				if (_viTank->cannonAngle > _viTank->cannonMaxAngle) _viTank->cannonAngle = _viTank->cannonMaxAngle;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (_viTank->isLeft)
			{
				_viTank->cannonAngle += 0.01f;
				if (_viTank->cannonAngle > _viTank->cannonMinAngle) _viTank->cannonAngle = _viTank->cannonMinAngle;
			}
			else
			{
				_viTank->cannonAngle -= 0.01f;
				if (_viTank->cannonAngle < _viTank->cannonMinAngle) _viTank->cannonAngle = _viTank->cannonMinAngle;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_SPACE))
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (_viTank->state != TANKSTATE::SHOOTREADY) _viTank->frameIndex = 0;
			_viTank->state = TANKSTATE::SHOOTREADY;
			_viTank->power++;
			if (_viTank->power > 200) _viTank->power = 200;
		}
	}
	else
	{
		_viTank = _vTank.begin();
		for (_viTank; _viTank != _vTank.end(); ++_viTank)
		{
			if (_viTank->state == TANKSTATE::SHOOTREADY)
			{
				if (_viTank->state != TANKSTATE::SHOOT) _viTank->frameIndex = 0;
				_viTank->state = TANKSTATE::SHOOT;
				_bullet->fire("문어탱 - 공격탄환", _viTank->x, _viTank->y, _viTank->cannonAngle, _viTank->power / 10);
				_viTank->power = 0;
			}
		}
	}

	image* mapImg = IMAGEMANAGER->findImage("배경지형");
	COLORREF mazenta = RGB(255, 0, 255);
	_viTank = _vTank.begin();
	for (_viTank; _viTank != _vTank.end(); ++_viTank)
	{
		if (_viTank->isLeft)
		{
			for (int i = _viTank->x - 25; i <= _viTank->x; i++)
			{
				COLORREF rgb = GetPixel(mapImg->getMemDC(), i, _viTank->y - 10);
				if (rgb != mazenta)
				{
					_viTank->x = i + 26;
					break;
				}
			}
		}
		else
		{
			for (int i = _viTank->x; i <= _viTank->x + 25; i++)
			{
				COLORREF rgb = GetPixel(mapImg->getMemDC(), i, _viTank->y - 10);
				if (rgb != mazenta)
				{
					_viTank->x = i - 26;
					break;
				}
			}
		}

		for (int i = _viTank->y; i <= camera->mapHeight; i++)
		{
			COLORREF rgb = GetPixel(mapImg->getMemDC(), _viTank->x, i);
			if (rgb != mazenta)
			{
				_viTank->y = i - 20;
				break;
			}
		}

		_viTank->count++;
		if (_viTank->count % 3 == 0)
		{
			if (_viTank->isLeft)
			{
				_viTank->frameIndex--;
				if (_viTank->frameIndex < 0)
				{
					if (_viTank->state == TANKSTATE::SHOOT) _viTank->state = TANKSTATE::WAIT;
					_viTank->frameIndex = getTankImg(_viTank->imgKey, _viTank->state)->getMaxFrameX();
				}
			}
			else
			{
				_viTank->frameIndex++;
				if (_viTank->frameIndex > getTankImg(_viTank->imgKey, _viTank->state)->getMaxFrameX())
				{
					if (_viTank->state == TANKSTATE::SHOOT) _viTank->state = TANKSTATE::WAIT;
					_viTank->frameIndex = 0;
				}
			}
		}
		if (_viTank->count >= 20) _viTank->count = 0;
		camera->viewPortSetting(_viTank->x, _viTank->y);
	}
	_bullet->update(camera);
}
void tankManager::render(LPCAMERA camera)
{
	HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN yellowPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	HPEN oldPen;

	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));

	image* tankImg;
	_viTank = _vTank.begin();
	for (_viTank; _viTank != _vTank.end(); ++_viTank)
	{
		tankImg = getTankImg(_viTank->imgKey, _viTank->state);
		if (_viTank->isLeft) tankImg->frameRender(getMemDC(), _viTank->x - 78 - camera->viewStartX + camera->marginX, _viTank->y - 50 - camera->viewStartY + camera->marginY, _viTank->frameIndex, 1);
		else tankImg->frameRender(getMemDC(), _viTank->x - 38 - camera->viewStartX + camera->marginX, _viTank->y - 50 - camera->viewStartY + camera->marginY, _viTank->frameIndex, 0);

		oldPen = (HPEN)SelectObject(getMemDC(), redPen);
		LineMake(getMemDC(), _viTank->x - camera->viewStartX + camera->marginX, _viTank->y - camera->viewStartY + camera->marginY, _viTank->x + cosf(_viTank->cannonAngle) * 50 - camera->viewStartX + camera->marginX, _viTank->y - sinf(_viTank->cannonAngle) * 50 - camera->viewStartY + camera->marginY);
		SelectObject(getMemDC(), yellowPen);
		LineMake(getMemDC(), _viTank->x - camera->viewStartX + camera->marginX, _viTank->y - camera->viewStartY + camera->marginY, _viTank->x + cosf(_viTank->cannonMinAngle) * 50 - camera->viewStartX + camera->marginX, _viTank->y - sinf(_viTank->cannonMinAngle) * 50 - camera->viewStartY + camera->marginY);
		LineMake(getMemDC(), _viTank->x - camera->viewStartX + camera->marginX, _viTank->y - camera->viewStartY + camera->marginY, _viTank->x + cosf(_viTank->cannonMaxAngle) * 50 - camera->viewStartX + camera->marginX, _viTank->y - sinf(_viTank->cannonMaxAngle) * 50 - camera->viewStartY + camera->marginY);
		SelectObject(getMemDC(), oldPen);

		if (_viTank->state == TANKSTATE::SHOOTREADY)
		{
			float pPer = (((float)_viTank->power) / 200.0f) * 100.0f;
			RECT rc = RectMakeCenter(_viTank->x - camera->viewStartX + camera->marginX, _viTank->y + 20 - camera->viewStartY + camera->marginY, 100, 10);
			RECT powerRc = RectMake(rc.left, rc.top + 1, pPer, 8);
			Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
			FillRect(getMemDC(), &powerRc, greenBrush);
		}
	}
	_bullet->render(camera);
	DeleteObject(redPen);
	DeleteObject(yellowPen);
	DeleteObject(greenBrush);
}

void tankManager::addTank(char* imgKey, float x, float y)
{
	tagTank tank;
	tank.x = x;
	tank.y = y;
	tank.cannonAngle = PI * 0.25;
	tank.cannonMinAngle = PI * 0.1;
	tank.cannonMaxAngle = PI * 0.4;
	tank.tankAngle = 0;
	tank.state = TANKSTATE::WAIT;
	tank.imgKey = imgKey;
	tank.frameIndex = 0;
	tank.isLeft = false;
	tank.power = 0;

	_vTank.push_back(tank);
}

image* tankManager::getTankImg(char* imgKey, TANKSTATE state)
{
	image* img = NULL;
	string key = imgKey;
	switch (state)
	{
	case TANKSTATE::WAIT:
	case TANKSTATE::MOVE:
		key += " - 대기";
		break;
	case TANKSTATE::SHOOTREADY:
		key += " - 공격준비";
		break;
	case TANKSTATE::SHOOT:
		key += " - 공격";
		break;
	}
	img = IMAGEMANAGER->findImage(key);
	
	return img;
}