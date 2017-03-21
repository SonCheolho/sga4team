#include "stdafx.h"
#include "effect.h"


void effect::createFX(int getEnumFX, int centerX, int centerY, int liveTime)
{
	tagFX _stFX;
	switch (getEnumFX)
	{
	//case ´«µ¢ÀÌ:
	//case ±¼·¯°¡´Â´«µ¢ÀÌ:
	//case »ç¶óÁö´Â´«µ¢ÀÌ:
	//	_stFX.height = _stFX.width = 76;
	//	break;
	//case ÀÛÀºÃÑ¾Ë:
	//	break;
	//case Å«ÃÑ¾Ë:
	//	break;
	case ÃÑ¾ËÈ÷Æ®:
		break;
	case ¸®½ºÆù:
		break;
	default:
		break;
	}
	_stFX.centerX = centerX;
	_stFX.centerY = centerY;
	_stFX.liveTimer = liveTime;
	//·ºÆ® °»½Å
	_stFX.rc = RectMakeCenter(_stFX.centerX, _stFX.centerY, _stFX.width, _stFX.height);

	//º¤ÅÍ ¼³Á¤
	_vFX.push_back(_stFX);
}

void effect::moveFX(int currentTime)
{
	for (int  i = 0; i < _vFX.size(); ++i)
	{
		if (_vFX[i].paturn == 0)
		{
			_vFX[i].liveTimer--;
			if (_vFX[i].liveTimer <= 0)
			{
				_vFX[i].paturn = -1;
			}
		}
	}
	for (int i = 0; i < _vFX.size(); ++i)
	{
		if (_vFX[i].paturn == -1)
		{
			_vFX.erase(_vFX.begin() + i);
			break;
		}
	}
}

HRESULT effect::init(void)
{
	return S_OK;
}

void effect::release(void)
{
}

void effect::update(void)
{
}

void effect::render(void)
{
	for (int i = 0; i < _vFX.size(); ++i)
	{
		//IMAGEMANAGER->frameRender();
	}
}
