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
		if (_vEnemy[i].paturn == 0 && _vEnemy[i].rc.top + _vEnemy[i].height / 2 < _vEnemy[i].centerY)
		{
			_vEnemy[i].rc.bottom += 4;
			_vEnemy[i].rc.top += 4;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = 대기;
				_vEnemy[i].paturn = 1;
			}
		}

		//개별
		if (_vEnemy[i].enemyNumber == 적1)// 빨간도깨비
		{
			if (_vEnemy[i].paturn == 1)
			{

			}
		}
		if (_vEnemy[i].enemyNumber == 적2)// 노란원숭이
		{

		}
		if (_vEnemy[i].enemyNumber == 적3)// 초록불쏘는놈
		{

		}
	}
}

void sb_enemy::pixelCollision()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i].paturn == 1 && !(_vEnemy[i].motion == 리스폰))
		{
			//좌우벽충돌
			for (int  i = 0; i < _vEnemy[i].centerX; i++)
			{

			}
			//바닥 충돌
			if (!(_vEnemy[i].motion == 아래점프 && _vEnemy[i].motion == 점프))
			{
				for (int i = _vEnemy[i].rc.bottom - _vEnemy[i].height / 2; i < _vEnemy[i].rc.bottom; i++)
				{
					COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _vEnemy[i].centerX, i);
					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//대각선 바닥 충돌
					if (r == 255 && g == 0 && b == 255)
					{
						_vEnemy[i].centerY = i - _vEnemy[i].height / 2;
						break;
					}

					//일반 바닥 충돌 (낙하 처리) 
					if (r == 255 && g == 0 && b == 255)
					{
						_vEnemy[i].centerY = i - _vEnemy[i].height / 2;
						break;
					}
				}
			}
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
