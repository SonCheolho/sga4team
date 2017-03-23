#include "stdafx.h"
#include "snowBrothers.h"

HRESULT snowBrothers::init(void)
{
	_testImage = IMAGEMANAGER->addImage("�׽�Ʈ���", "image/1_1.bmp", 672, 720);
	_collisionImage = IMAGEMANAGER->addImage("�浹����", "image/1_2.bmp", 672, 720, true, RGB(255, 0, 255));
	_enemyCollision = IMAGEMANAGER->addImage("�浹����2", "image/1_3.bmp", 672, 720);

	_sbPlayer = new sb_player;
	_sbPlayer->init();
	_sbBoss = new sb_boss;
	_sbBoss->init();
	_sbEnemy = new sb_enemy;
	_sbEnemy->init();

	return S_OK;
}

void snowBrothers::release(void)
{
	_sbPlayer->release();
	SAFE_DELETE(_sbPlayer);
	_sbBoss->release();
	SAFE_DELETE(_sbBoss);
	_sbEnemy->release();
	SAFE_DELETE(_sbEnemy);
}

void snowBrothers::update(void)
{
	_sbPlayer->update();
	_sbBoss->update();
	_sbEnemy->update();
}

void snowBrothers::render(void)
{
	_testImage->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		_collisionImage->render(getMemDC());
	}
	if (KEYMANAGER->isToggleKey(VK_F12))
	{
		_enemyCollision->render(getMemDC());
	}

	_sbPlayer->render();
	_sbBoss->render();
	_sbEnemy->render();
}
