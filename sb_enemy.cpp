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
		if (_vEnemy[i].paturn == 0 && _vEnemy[i].rc.top + _vEnemy[i].height / 2 < _vEnemy[i].centerY)
		{
			_vEnemy[i].rc.bottom += 4;
			_vEnemy[i].rc.top += 4;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = ���;
				_vEnemy[i].paturn = 1;
			}
		}

		//����
		if (_vEnemy[i].enemyNumber == ��1)// ����������
		{
			if (_vEnemy[i].paturn == 1)
			{

			}
		}
		if (_vEnemy[i].enemyNumber == ��2)// ���������
		{

		}
		if (_vEnemy[i].enemyNumber == ��3)// �ʷϺҽ�³�
		{

		}
	}
}

void sb_enemy::pixelCollision()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i].paturn == 1 && !(_vEnemy[i].motion == ������))
		{
			//�¿캮�浹
			for (int  i = 0; i < _vEnemy[i].centerX; i++)
			{

			}
			//�ٴ� �浹
			if (!(_vEnemy[i].motion == �Ʒ����� && _vEnemy[i].motion == ����))
			{
				for (int i = _vEnemy[i].rc.bottom - _vEnemy[i].height / 2; i < _vEnemy[i].rc.bottom; i++)
				{
					COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), _vEnemy[i].centerX, i);
					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//�밢�� �ٴ� �浹
					if (r == 255 && g == 0 && b == 255)
					{
						_vEnemy[i].centerY = i - _vEnemy[i].height / 2;
						break;
					}

					//�Ϲ� �ٴ� �浹 (���� ó��) 
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
