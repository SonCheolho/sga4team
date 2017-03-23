#include "stdafx.h"
#include "sb_enemy.h"

void sb_enemy::enemySet(ENEMY_NUMBER EenemyNum, LOOK currentLook, int centerX, int centerY, int def)
{
	tagEnemy _stEnemy;
	ZeroMemory(&_stEnemy, sizeof(_stEnemy));

	_stEnemy.enemyNumber = EenemyNum;
	_stEnemy.look = currentLook;
	_stEnemy.def = def;
	_stEnemy.motion = 리스폰;

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
		//리스폰 (공통)
		if (_vEnemy[i].motion == 리스폰 && _vEnemy[i].rc.top + _vEnemy[i].height / 2 < _vEnemy[i].centerY)
		{
			_vEnemy[i].rc.bottom += 4;
			_vEnemy[i].rc.top += 4;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = 대기;
			}
		}

		//개별
		if (_vEnemy[i].enemyNumber == 적1)
		{
		}
		if (_vEnemy[i].enemyNumber == 적2)
		{

		}
		if (_vEnemy[i].enemyNumber == 적3)
		{

		}
	}
}

HRESULT sb_enemy::init(void)
{

	//이미지 초기화
	//적1



	//적2



	//적3


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
