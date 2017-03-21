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
		_stItem.itemNumber = _viItemList[findItemList(보너스1)].itemNumber;
		_stItem.point = _viItemList[findItemList(보너스1)].point;
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
		if (_vItem[i].itemNumber == 보너스1 || _vItem[i].itemNumber == 보너스2)
		{
			//일단 움직인다
			if (_vItem[i].paturn == 0)//지형위에 멈추지 않은 상태의 패턴
			{
				_vItem[i].centerY += speed;
			
				//스테이지의 맨 아래지형위에 안착
				for (int j = _vItem[i].centerY - _vItem[i].height / 2; j < _vItem[i].centerY + _vItem[i].height / 2; j++)
				{
					COLORREF colorTemp = GetPixel(dc, _vItem[i].centerX, j);
					int R = GetRValue(colorTemp);
					int G = GetGValue(colorTemp);
					int B = GetBValue(colorTemp);
					if (R == 0 && G == 0 && B == 0)
					{
						_vItem[i].paturn = 1;//지형위에 안착
						break;
					}
				}
			}
			//지형에 안착했다면 라이브 타이머 작동
			if (_vItem[i].paturn == 1)
			{
				_vItem[i].liveTimer--;
				if (_vItem[i].liveTimer <= 0)
				{
					_vItem[i].paturn = -1;
				}
			}

			//보너스 아이템 렉트 갱신
			_vItem[i].rc = RectMakeCenter(_vItem[i].centerX, _vItem[i].centerY, _vItem[i].width, _vItem[i].height);
		}
	}
}

void item::moveItem()
{
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (!(_vItem[i].itemNumber == 보너스1 && _vItem[i].itemNumber == 보너스2))
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
	//초밥
	itemSetting(초밥1, 100);
	itemSetting(초밥2, 200);
	itemSetting(초밥3, 300);
	itemSetting(초밥4, 400);
	itemSetting(초밥5, 600);
	itemSetting(초밥6, 800);
	itemSetting(초밥7, 1000);
	itemSetting(초밥8, 1200);
	itemSetting(초밥9, 1500);
	itemSetting(초밥10, 2000);
	//물약
	itemSetting(빨간물약, 1000);
	itemSetting(노란물약, 1000);
	itemSetting(초록물약, 1000);
	itemSetting(파란물약, 1000);
	//보너스
	itemSetting(보너스1, 10000);
	itemSetting(보너스2, 20000);

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
	//아이템 이미지 렌더
	//아이템 렉트
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _vItem.size(); ++i)
		{
			Rectangle(getMemDC(), _vItem[i].rc.left, _vItem[i].rc.top, _vItem[i].rc.right, _vItem[i].rc.bottom);
		}
	}
	//아이템 이미지
	for (int i = 0; i < _vItem.size(); ++i)
	{
		if (_vItem[i].paturn != -1)
		{
			if (_vItem[i].itemNumber == 빨간물약 || _vItem[i].itemNumber == 노란물약 || _vItem[i].itemNumber == 초록물약 || _vItem[i].itemNumber == 파란물약)
			{
				int frameY;
				switch (_vItem[i].itemNumber)
				{
				빨간물약:
					frameY = 0;
					break;
				노란물약:
					frameY = 1;
					break;
				초록물약:
					frameY = 2;
					break;
				파란물약:
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
