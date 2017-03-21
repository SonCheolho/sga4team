#include "stdafx.h"
#include "item.h"


void item::itemSetting(int itemNumber, int point)
{
	tagItem _stItem;
	ZeroMemory(&_stItem, sizeof(_stItem));
	_stItem.itemNumber = itemNumber;
	_stItem.point = point;
	_vItemList.push_back(_stItem);
}

int item::findItemList(int itemNumber)
{
	for (int i = 0; i < _vItemList.size(); ++i)
	{
		if (_vItemList[i].itemNumber == itemNumber)
		{
			return i;
		}
	}
}

void item::createItem(int itemNumber, int centerX, int centerY)
{
	tagItem _stItem;
	ZeroMemory(&_stItem, sizeof(_stItem));

	_stItem.itemNumber = _viItemList[findItemList(itemNumber)].itemNumber;
	_stItem.point = _viItemList[findItemList(itemNumber)].point;
	_stItem.centerX = centerX;
	_stItem.centerY = centerY;
	_stItem.liveTimer = 1000;
	_vItemList.push_back(_stItem);

}

void item::createBonusItem(int maxItem)
{
	tagItem _stItem;
	ZeroMemory(&_stItem, sizeof(_stItem));
	for (int i = 0; i < maxItem; i++)
	{
		_stItem.itemNumber = _viItemList[findItemList(���ʽ�1)].itemNumber;
		_stItem.point = _viItemList[findItemList(���ʽ�1)].point;
		_stItem.centerX = RND->getFromIntTo(50, WINSIZEX - 50);
		_stItem.centerY = -100;
		_stItem.liveTimer = 300;
		_vItemList.push_back(_stItem);
	}
}

void item::moveBonusItem(HDC dc, int speed)
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i].itemNumber == ���ʽ�1 || _vItem[i].itemNumber == ���ʽ�2)
		{
			//�ϴ� �����δ�
			if (_vItem[i].paturn == 0)//�������� ������ ���� ������ ����
			{
				_vItem[i].centerY += speed;
			
				//���������� �� �Ʒ��������� ����
				for (int j = _vItem[i].centerY - _vItem[i].height / 2; j < _vItem[i].centerY + _vItem[i].height / 2; j++)
				{
					COLORREF colorTemp = GetPixel(dc, _vItem[i].centerX, j);
					int R = GetRValue(colorTemp);
					int G = GetGValue(colorTemp);
					int B = GetBValue(colorTemp);
					if (R == 0 && G == 0 && B == 0)
					{
						_vItem[i].paturn = 1;//�������� ����
						break;
					}
				}
			}
			//������ �����ߴٸ� ���̺� Ÿ�̸� �۵�
			if (_vItem[i].paturn == 1)
			{
				_vItem[i].liveTimer--;
				if (_vItem[i].liveTimer <= 0)
				{
					_vItem[i].paturn = -1;
				}
			}

			//���ʽ� ������ ��Ʈ ����
			_vItem[i].rc = RectMakeCenter(_vItem[i].centerX, _vItem[i].centerY, _vItem[i].width, _vItem[i].height);
		}
	}
}

void item::moveItem()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (!(_vItem[i].itemNumber == ���ʽ�1 && _vItem[i].itemNumber == ���ʽ�2))
		{
			_vItem[i].liveTimer--;
			if (_vItem[i].liveTimer <= 0)
			{
				_vItem[i].paturn = -1;
			}
		}
	}
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i].paturn == -1)
		{
			_vItem.erase(_vItem.begin() + i);
			break;
		}
	}

}

HRESULT item::init(void)
{
	//�ʹ�
	itemSetting(�ʹ�1, 100);
	itemSetting(�ʹ�2, 200);
	itemSetting(�ʹ�3, 300);
	itemSetting(�ʹ�4, 400);
	itemSetting(�ʹ�5, 600);
	itemSetting(�ʹ�6, 800);
	itemSetting(�ʹ�7, 1000);
	itemSetting(�ʹ�8, 1200);
	itemSetting(�ʹ�9, 1500);
	itemSetting(�ʹ�10, 2000);
	//����
	itemSetting(��������, 1000);
	itemSetting(�������, 1000);
	itemSetting(�ʷϹ���, 1000);
	itemSetting(�Ķ�����, 1000);
	//���ʽ�
	itemSetting(���ʽ�1, 10000);
	itemSetting(���ʽ�2, 20000);

	return S_OK;
}

void item::release(void)
{
}

void item::update(void)
{
}

void item::render(void)
{
	//������ �̹��� ����
	//������ ��Ʈ
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			Rectangle(getMemDC(), _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].rc.right, _vItem[i].rc.bottom);
		}
	}
	//������ �̹���
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i].paturn != -1)
		{
			if (_vItem[i].itemNumber == �������� || _vItem[i].itemNumber == ������� || _vItem[i].itemNumber == �ʷϹ��� || _vItem[i].itemNumber == �Ķ�����)
			{
				int frameY;
				switch (_vItem[i].itemNumber)
				{
				��������:
					frameY = 0;
					break;
				�������:
					frameY = 1;
					break;
				�ʷϹ���:
					frameY = 2;
					break;
				�Ķ�����:
					frameY = 3;
					break;
				}
				//IMAGEMANAGER->frameRender();
			}
			else
			{
				//IMAGEMANAGER->frameRender();
			}
		}
	}
}
