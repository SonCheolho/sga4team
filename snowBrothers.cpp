#include "stdafx.h"
#include "snowBrothers.h"

HRESULT snowBrothers::init(void)
{
	_testImage = 
	_collisionImage = IMAGEMANAGER->addImage("충돌용배경", "image/1_2.bmp", 672, 720, true, RGB(255, 0, 255));
	
	_sbPlayer = new sb_player;
	_sbPlayer->init();
	_sbBoss = new sb_boss;
	_sbBoss->init();

	return S_OK;
}

void snowBrothers::release(void)
{
	_sbPlayer->release();
	SAFE_DELETE(_sbPlayer);
	_sbBoss->release();
	SAFE_DELETE(_sbBoss);
}

void snowBrothers::update(void)
{
	_sbPlayer->update();
	_sbBoss->update();
}

void snowBrothers::render(void)
{
	_testImage->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		_collisionImage->render(getMemDC());
	}

	_sbPlayer->render();
	_sbBoss->render();
}
