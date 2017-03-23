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
			_vEnemy[i].rc.bottom += 10;
			_vEnemy[i].rc.top += 10;
			//
			if (_vEnemy[i].rc.top + _vEnemy[i].height / 2 >= _vEnemy[i].centerY)
			{
				_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);
				_vEnemy[i].motion = ���;
				_vEnemy[i].paturn = 1;
			}
		}

		//����
		//�Ϲ����� ������ �³� �쳡���� �ɾ�ٴϴٰ� ���� �������� ������ �ö󰡴��� or ���������� ��� �ɾ���� ����.
		//#1
		if (_vEnemy[i].paturn == 1 && _vEnemy[i].motion == ���)
		{
			//���� ����
			if (_vEnemy[i].look == ��)	_vEnemy[i].look = ��;
			else if (_vEnemy[i].look == ��)	_vEnemy[i].look = ��;
			_vEnemy[i].paturn = 2;
			_vEnemy[i].motion = �ȱ�;

		}

		//#2
		if (_vEnemy[i].paturn == 2 && _vEnemy[i].motion == �ȱ�)
		{
			if (_vEnemy[i].look == ��)
			{
				_vEnemy[i].centerX ++;
				//�� �̵� ����
				if (_vEnemy[i].centerX + _vEnemy[i].width / 2 >= WINSIZEX)
				{
					_vEnemy[i].look = ��;
				}
			}
			else if (_vEnemy[i].look == ��)
			{
				_vEnemy[i].centerX --;
				//�� �̵� ����
				if (_vEnemy[i].centerX - _vEnemy[i].width / 2 <= 0)
				{
					_vEnemy[i].look = ��;
				}
			}
			//��Ʈ ����
			_vEnemy[i].rc = RectMakeCenter(_vEnemy[i].centerX, _vEnemy[i].centerY, _vEnemy[i].width, _vEnemy[i].height);

		}


		if (_vEnemy[i].enemyNumber == ��1)// ����������
		{

		}
		if (_vEnemy[i].enemyNumber == ��2)// ���������
		{

		}
		if (_vEnemy[i].enemyNumber == ��3)// �ʷϺҽ�³�
		{

		}

	}
}

void sb_enemy::snowBallMoving()
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		if (_vEnemy[i].motion == �򴫹�ġ || _vEnemy[i].motion == �Ķ�����ġ)
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
			//�¿캮�浹 (����)
			
			// ��
			for (int j = _vEnemy[i].rc.left; j < _vEnemy[i].centerX; j++)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), j, _vEnemy[i].centerY);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);


				if (r == 255 && g == 0 && b == 0)
				{
					_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
					_vEnemy[i].look = ��;
					break;
				}
			}
			// ��
			for (int j = _vEnemy[i].centerX; j < _vEnemy[i].rc.right; j++)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), j, _vEnemy[i].centerY);
				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);


				if (r == 0 && g == 0 && b == 255)
				{
					_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
					_vEnemy[i].look = ��;
					break;
				}
			}


			//�ٴ� �浹
			if (!(_vEnemy[i].motion == ����))
			{
				for (int j = _vEnemy[i].rc.bottom - _vEnemy[i].height / 2; j < _vEnemy[i].rc.bottom; j++)
				{
					COLORREF color = GetPixel(IMAGEMANAGER->findImage("�浹����")->getMemDC(), _vEnemy[i].centerX, j);
					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//�밢�� �ٴ� �浹
					if (r == 255 && g == 0 && b == 255)
					{
						_vEnemy[i].centerY = j - _vEnemy[i].height / 2;
						break;
					}

					//�Ϲ� �ٴ� �浹 (���� ó��) 
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
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		enemySet(ENEMY_NUMBER::��1, LOOK::��, 100, 200, 0);
		enemySet(ENEMY_NUMBER::��1, LOOK::��, 250, 300, 0);
		enemySet(ENEMY_NUMBER::��1, LOOK::��, 400, 400, 0);
	}
	enemyMoving();
	pixelCollision();
}

void sb_enemy::render(void)
{
	for (int i = 0; i < _vEnemy.size(); ++i)
	{
		//��Ʈ
		if (KEYMANAGER->isToggleKey(VK_F1))
		{
			Rectangle(getMemDC(), _vEnemy[i].rc.left, _vEnemy[i].rc.top, _vEnemy[i].rc.right, _vEnemy[i].rc.bottom);
		}
		//�̹���
		if (_vEnemy[i].motion != �򴫹�ġ)
		{
			switch (_vEnemy[i].enemyNumber)
			{
			case ��1:
				break;
			case ��2:
				break;
			case ��3:
				break;
			default:
				break;
			}
		}
		//����ġ�� �ϼ��Ǿ��� ��
		if (_vEnemy[i].motion == �򴫹�ġ)
		{

		}
	}


}
