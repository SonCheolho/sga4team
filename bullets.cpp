#include "stdafx.h"
#include "bullets.h"
//==================================================================
//		## bullet ## �����Ѿ� (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
//�Ѿ��̹����̸�, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
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

//�Ѿ˹߻� (�Ѿ���ġ, ����, �ӵ�)
void bullet::fire(float x, float y, float angle, float speed)
{
	//�Ѿ˹߻� ������ �����Ѵ�
	if (_bulletMax < _vBullet.size()) return;

	//�Ѿ˱���ü ������ ���Ϳ� ���
	//�Ѿ� ����ü ����
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

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

//�Ѿ˹���
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

		//�Ѿ��� ��Ÿ����� Ŀ������ �����Ҵ��� �̹��� �� �ݺ��� ����
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
//		## missile ## (missile[10] => �迭ó�� �̸������صΰ� �Ѿ˹߻�)
//==================================================================
//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
HRESULT missile::init(int bulletMax, float range)
{
	//��Ÿ� �ʱ�ȭ
	_range = range;

	//�Ѿ� ����ü �ʱ�ȭ
	for (int i = 0; i < bulletMax; i++)
	{
		//�Ѿ� ����ü ����
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.bulletImage = new image;
		bullet.bulletImage->init("missile.bmp", 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.speedY = 5.0f;
		bullet.fire = false;

		//���Ϳ� ���
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
	//�Ѿ˹���
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

//�Ѿ˹߻�
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

//�Ѿ˹���
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

		//�Ѿ��� ��Ÿ����� Ŀ������
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//==================================================================
//		## missileM1 ## (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
HRESULT missileM1::init(int bulletMax, float range)
{
	//�Ѿ˰��� ��Ÿ� �ʱ�ȭ
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

//�Ѿ˹߻�
void missileM1::fire(float x, float y)
{
	//�Ѿ˹߻� ������ �����Ѵ�
	if (_bulletMax < _vBullet.size()) return;

	//�Ѿ˱���ü ������ ���Ϳ� ���
	//�Ѿ� ����ü ����
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

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}

//�Ѿ˹���
void missileM1::move(void)
{
	_viBullet = _vBullet.begin();
	for (; _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speedY;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->bulletImage->getFrameWidth(),
			_viBullet->bulletImage->getFrameHeight());

		//�Ѿ��� ��Ÿ����� Ŀ������ �����Ҵ��� �̹��� �� �ݺ��� ����
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY,
			_viBullet->x, _viBullet->y))
		{
			//���⼭ ����
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
//		## parabolaBullet ## (������ źȯ)
//==================================================================
//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
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

//�Ѿ˹߻�
void parabolaBullet::fire(char* imageName, float x, float y, float angle, float speed)
{
	//�Ѿ˱���ü ������ ���Ϳ� ���
	//�Ѿ� ����ü ����
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

	//���Ϳ� ���
	_vBullet.push_back(bullet);
}
//�Ѿ˹���
void parabolaBullet::move(LPCAMERA camera)
{
	COLORREF mazenta = RGB(255, 0, 255);
	image* mapImg = IMAGEMANAGER->findImage("�������");
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

		//�Ѿ��� ��Ÿ����� Ŀ������ �����Ҵ��� �̹��� �� �ݺ��� ����
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