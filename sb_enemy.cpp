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
			_vEnemy[i].rc.bottom += 10;
			_vEnemy[i].rc.top += 10;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = 대기;
				_vEnemy[i].paturn = 1;
			}
		}

		//개별
		//일반적인 패턴은 좌끝 우끝으로 걸어다니다가 지형 끝지점과 만나면 올라가던가 or 내려가던가 계속 걸어가던가 랜덤.
		//#1
		if (_vEnemy[i].paturn == 1 && _vEnemy[i].motion == 대기)
		{
			//방향 랜덤
			if (_vEnemy[i].look == 우)	_vEnemy[i].look = 좌;
			else if (_vEnemy[i].look == 좌)	_vEnemy[i].look = 우;
			_vEnemy[i].paturn = 2;
			_vEnemy[i].motion = 걷기;

		}

		//#2
		if (_vEnemy[i].paturn == 2 && _vEnemy[i].motion == 걷기)
		{
			if (_vEnemy[i].look == 우)
			{
				_vEnemy[i].centerX ++;
				//우 이동 금지
				if (_vEnemy[i].centerX + _vEnemy[i].width / 2 >= WINSIZEX)
				{
					_vEnemy[i].look = 좌;
				}
			}
			else if (_vEnemy[i].look == 좌)
			{
				_vEnemy[i].centerX --;
				//좌 이동 금지
				if (_vEnemy[i].centerX - _vEnemy[i].width / 2 <= 0)
				{
					_vEnemy[i].look = 우;
				}
			}
			//렉트 갱신
			_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);

		}


		if (_vEnemy[i].enemyNumber == 적1)// 빨간도깨비
		{

		}
		if (_vEnemy[i].enemyNumber == 적2)// 노란원숭이
		{

		}
		if (_vEnemy[i].enemyNumber == 적3)// 초록불쏘는놈
		{

		}

	}
}

void sb_enemy::snowBallMoving()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i].motion == 흰눈뭉치 || _vEnemy[i].motion == 파란눈뭉치)
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
			//좌우벽충돌 (공통)
			
			// 좌
			for (int j = _vEnemy[i].rc.left; j < _vEnemy[i].centerX; j++)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), j, _vEnemy[i].centerY);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);


				if (r == 255 && g == 0 && b == 0)
				{
					_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
					_vEnemy[i].look = 우;
					break;
				}
			}
			// 우
			for (int j = _vEnemy[i].centerX; j < _vEnemy[i].rc.right; j++)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), j, _vEnemy[i].centerY);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);


				if (r == 0 && g == 0 && b == 255)
				{
					_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
					_vEnemy[i].look = 좌;
					break;
				}
			}


			//바닥 충돌
			if (!(_vEnemy[i].motion == 점프))
			{
				for (int j = _vEnemy[i].rc.bottom - _vEnemy[i].height / 2; j < _vEnemy[i].rc.bottom; j++)
				{
					COLORREF color = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _vEnemy[i].centerX, j);
					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//대각선 바닥 충돌
					if (r == 255 && g == 0 && b == 255)
					{
						_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
						break;
					}

					//일반 바닥 충돌 (낙하 처리) 
					if (!(r == 255 && g == 0 && b == 255))
					{
						_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
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
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		enemySet(ENEMY_NUMBER::적1, LOOK::좌, 100, 200, 0);
		enemySet(ENEMY_NUMBER::적1, LOOK::우, 250, 300, 0);
		enemySet(ENEMY_NUMBER::적1, LOOK::우, 400, 400, 0);
	}
	enemyMoving();
	pixelCollision();
}

void sb_enemy::render(void)
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		//렉트
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), _vEnemy[i].rc.left, _vEnemy[i].rc.top, _vEnemy[i].rc.right, _vEnemy[i].rc.bottom);
		}
		//이미지
		if (_vEnemy[i].motion != 흰눈뭉치)
		{
			switch (_vEnemy[i].enemyNumber)
			{
			case 적1:
				break;
			case 적2:
				break;
			case 적3:
				break;
			default:
				break;
			}
		}
		//눈뭉치가 완성되었을 때
		if (_vEnemy[i].motion == 흰눈뭉치)
		{

		}
	}


}
