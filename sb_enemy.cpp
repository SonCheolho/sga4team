#include "stdafx.h"
#include "sb_enemy.h"

void sb_enemy::enemySet(ENEMY_NUMBER EenemyNum, LOOK currentLook, int centerX, int centerY, int def)
{
	tagEnemy _stEnemy;
	ZeroMemory(&_stEnemy, sizeof(_stEnemy));

	_stEnemy.enemyNumber = EenemyNum;
	_stEnemy.look = currentLook;
	_stEnemy.def = def;
	_stEnemy.motion = ������;

	_stEnemy.centerX = centerX;
	_stEnemy.centerY = centerY;
	_stEnemy.width = 100;
	_stEnemy.height = 100;
	_stEnemy.rc = RectMakeCenter(centerX, centerY - WINSIZEY, _stEnemy.width, _stEnemy.height);

	_vEnemy.push_back(_stEnemy);
}

void sb_enemy::enemyMoving()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		//������ (����)
		if (_vEnemy[i].motion == ������ && _vEnemy[i].rc.top + _vEnemy[i].height / 2 < _vEnemy[i].centerY)
		{
			_vEnemy[i].rc.bottom += 4;
			_vEnemy[i].rc.top += 4;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = ���;
			}
		}

		//����
		if (_vEnemy[i].enemyNumber == ��1)
		{
		}
		if (_vEnemy[i].enemyNumber == ��2)
		{

		}
		if (_vEnemy[i].enemyNumber == ��3)
		{

		}
	}
}

HRESULT sb_enemy::init(void)
{

	//�̹��� �ʱ�ȭ
	//��1



	//��2



	//��3


	return S_OK;
}

void sb_enemy::release(void)
{
}

void sb_enemy::update(void)
{
}

void sb_enemy::render(void)
{
}