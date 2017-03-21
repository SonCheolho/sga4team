#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	//����(�÷��̾�) �̹��� �ʱ�ȭ �� ��ġ����
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;
	_rc = RectMake(_x, _y, 52, 64);

	//�̻���Ŭ���� ���� �� �ʱ�ȭ
	_missile = new missile;
	_missile->init(10, 500);
	_missileM1 = new missileM1;
	_missileM1->init(5, 600);

	//ü�¹� Ŭ���� ������ �ʱ�ȭ
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _rocket->getX(), _rocket->getY() - 50, 50, 10);
	//���� �ʱ�ȭ
	_maxHp = 100;
	_currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void player::release(void)
{
	//�̻���Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);
	SAFE_DELETE(_missileM1);

	//ü�¹� Ŭ���� ����
	SAFE_DELETE(_hpBar);
}

void player::update(void)
{
	//�÷��̾� �����̸鼭 ȭ������� �������� ó��
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		//�̹����� ��ǥ �����̱�
		_rocket->setX(_rocket->getX() - 5);
		_x -= 5;
	}
	//�÷��̾� �����̸鼭 ȭ������� �������� ó��
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() + _rocket->getWidth() < WINSIZEX)
	{
		//�̹����� ��ǥ �����̱�
		_rocket->setX(_rocket->getX() + 5);
		_x += 5;
	}
	//�Ѿ˹߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//ǡ�̾�~~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_missileM1->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//�̻��� Ŭ���� ������Ʈ
	_missile->update();
	_missileM1->update();

	//��Ʈ�� ��ǥ��ŭ ��� ������Ʈ ���ش�
	_rc = RectMake(_x, _y, 52, 64);

	//�浹�Լ�
	this->collision();

	//ü�¹� ������Ʈ
	_hpBar->update();
	//ü�¹ٰ� �÷��̾� �Ӹ����� ����ٴϰ� �����
	_hpBar->setX(_rocket->getX());
	_hpBar->setY(_rocket->getY() - 15);
	_hpBar->setGauge(_currentHp, _maxHp);

	/*
	//���̺�
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//atoi => ���ڸ� ������
		//itoa => ������ ���ڷ�
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(_rocket->getX(), temp, 10));
		vStr.push_back(itoa(_rocket->getY(), temp, 10));
		vStr.push_back(itoa(_currentHp, temp, 10));

		TXTDATA->txtSave("save.txt", vStr);
	}
	//�ε�
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save.txt");
		_rocket->setX(atoi(vStr[0].c_str()));
		_rocket->setY(atoi(vStr[1].c_str()));
		_currentHp = atoi(vStr[2].c_str());
	}
	*/

}

void player::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), _rc);
	}
	//�����̹��� ����
	_rocket->render(getMemDC());

	//�̻��� Ŭ���� ����
	_missile->render();
	_missileM1->render();

	//ü�¹� ����
	_hpBar->render();
}

void player::removeMissileM1(int index)
{
	_missileM1->removeBullet(index);
}

void player::collision(void)
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_missileM1->removeBullet(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}
