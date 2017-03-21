#include "stdafx.h"
#include "bullets.h"
//==================================================================
//		## bullet ## 공용총알 (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
//총알이미지이름, 총알갯수, 총알사거리로 초기화
HRESULT bullet::init(char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bullet::release(void)
{
	_vBullet.clear();
}

void bullet::update(void)
{
	move();
}

void bullet::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

//총알발사 (총알위치, 각도, 속도)
void bullet::fire(float x, float y, float angle, float speed)
{
	//총알발사 갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	//총알구조체 선언후 벡터에 담기
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bullet.angle = angle;
	bullet.speedX = speed;
	bullet.speedY = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getWidth(),
		bullet.bulletImage->getHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

//총알무브
void bullet::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speedX;
		_viBullet->y += (-sinf(_viBullet->angle)) * _viBullet->speedY;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getWidth(),
			_viBullet->bulletImage->getHeight());

		//총알이 사거리보다 커졌을때 동적할당한 이미지 및 반복자 삭제
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

//==================================================================
//		## missile ## (missile[10] => 배열처럼 미리장전해두고 총알발사)
//==================================================================
//총알갯수, 총알사거리로 초기화
HRESULT missile::init(int bulletMax, float range)
{
	//사거리 초기화
	_range = range;

	//총알 구조체 초기화
	for (int i = 0; i < bulletMax; i++)
	{
		//총알 구조체 선언
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.speedY = 5.0f;
		bullet.fire = false;

		//벡터에 담기
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void missile::release(void)
{
	_vBullet.clear();
}

void missile::update(void)
{
	//총알무브
	move();
}

void missile::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

//총알발사
void missile::fire(float x, float y)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;

		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		break;
	}
}

//총알무브
void missile::move(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->y -= _viBullet->speedY;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//==================================================================
//		## missileM1 ## (쏠때마다 한발씩 장전해서 발사 - 자동삭제)
//==================================================================
//총알갯수, 총알사거리로 초기화
HRESULT missileM1::init(int bulletMax, float range)
{
	//총알갯수 사거리 초기화
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void missileM1::release(void)
{
	_vBullet.clear();
}

void missileM1::update(void)
{
	move();
}
void missileM1::render(void)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->bulletImage->getFrameX(), 0);

		_viBullet->count++;
		if (_viBullet->count % 10 == 0)
		{
			_viBullet->bulletImage->setFrameX(_viBullet->bulletImage->getFrameX() + 1);
			if (_viBullet->bulletImage->getFrameX() >= _viBullet->bulletImage->getMaxFrameX())
			{
				_viBullet->bulletImage->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}

}

//총알발사
void missileM1::fire(float x, float y)
{
	//총알발사 갯수를 제한한다
	if (_bulletMax < _vBullet.size()) return;

	//총알구조체 선언후 벡터에 담기
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = new image;
	bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speedY = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}

//총알무브
void missileM1::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speedY;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//총알이 사거리보다 커졌을때 동적할당한 이미지 및 반복자 삭제
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//여기서 삭제
			SAFE_DELETE(_viBullet->bulletImage);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}

//==================================================================
//		## parabolaBullet ## (포물선 탄환)
//==================================================================
//총알갯수, 총알사거리로 초기화
HRESULT parabolaBullet::init(void)
{
	return S_OK;
}
void parabolaBullet::release(void)
{
	_vBullet.clear();
}
void parabolaBullet::update(LPCAMERA camera)
{
	move(camera);
}
void parabolaBullet::render(LPCAMERA camera)
{
	_viBullet = _vBullet.begin();
	for (_viBullet; _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->bulletImage->frameRender(getMemDC(), _viBullet->rc.left - camera->viewStartX + camera->marginX, _viBullet->rc.top - camera->viewStartY + camera->marginY, 9, 0);
	}
}

//총알발사
void parabolaBullet::fire(char* imageName, float x, float y, float angle, float speed)
{
	//총알구조체 선언후 벡터에 담기
	//총알 구조체 선언
	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.bulletImage = IMAGEMANAGER->findImage(imageName);
	bullet.angle = angle;
	bullet.speedX = speed;
	bullet.speedY = speed;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.bulletImage->getFrameWidth(),
		bullet.bulletImage->getFrameHeight());

	//벡터에 담기
	_vBullet.push_back(bullet);
}
//총알무브
void parabolaBullet::move(LPCAMERA camera)
{
	COLORREF mazenta = RGB(255, 0, 255);
	image* mapImg = IMAGEMANAGER->findImage("배경지형");
	_viBullet = _vBullet.begin();
	int num = 0;
	for (; _viBullet != _vBullet.end();)
	{
		if (num == 0) camera->viewPortSetting(_viBullet->x, _viBullet->y);

		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speedX;
		_viBullet->y += (-sinf(_viBullet->angle)) * _viBullet->speedY;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameWidth());
		_viBullet->speedY -= 0.3f;

		bool mapCollision = false;
		for (int i = _viBullet->rc.left; i <= _viBullet->rc.right; i++)
		{
			for (int l = _viBullet->rc.top; l < _viBullet->rc.bottom; l++)
			{
				if (8 >= getDistance(_viBullet->x, _viBullet->y, i, l)
					&& i >= 0 && i <= mapImg->getWidth()
					&& l >= 0 && l <= mapImg->getHeight())
				{
					COLORREF rgb = GetPixel(mapImg->getMemDC(), i, l);
					if (rgb != mazenta)
					{
						HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
						HBRUSH oldBrush = (HBRUSH)SelectObject(mapImg->getMemDC(), hBrush);
						HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
						HPEN oldPen = (HPEN)SelectObject(mapImg->getMemDC(), hPen);
						EllipseMakeCenter(mapImg->getMemDC(), i, l, 100, 80);
						SelectObject(mapImg->getMemDC(), oldBrush);
						SelectObject(mapImg->getMemDC(), oldPen);
						DeleteObject(hBrush);
						DeleteObject(hPen);
						camera->switchViewDelay = 100;
						mapCollision = true;
					}
				}
			}
		}

		//총알이 사거리보다 커졌을때 동적할당한 이미지 및 반복자 삭제
		if (_viBullet->y > camera->mapHeight || mapCollision)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
		num++;
	}
}