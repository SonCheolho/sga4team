#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init(void)
{
	//�̴Ͼ� ����
	this->setMinion();

	//�Ѿ�Ŭ���� ���� �� �ʱ�ȭ
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release(void)
{
	//�Ѿ� Ŭ���� ����
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	//�Ѿ� Ŭ���� ������Ʈ
	_bullet->update();

	this->minionBulletFire();

	//�浹�Լ�
	this->collision();
}

void enemyManager::render(void)
{
	//���Ϳ� ��� �̴Ͼ�� ����
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	//�Ѿ� Ŭ���� ����
	_bullet->render();
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo = new minion;
			ufo->init("ufo", PointMake(50 + j * 100, 100 + i * 100));

			_vMinion.push_back(ufo);
		}
	}
}

void enemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI / 2, 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

void enemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc,
			&_pl->getRocketImage()->boundingBox()))
		{
			_bullet->removeBullet(i);
			_pl->hitDamage(10);
			break;
		}
	}
}
