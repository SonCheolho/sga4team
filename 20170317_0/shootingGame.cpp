#include "stdafx.h"
#include "shootingGame.h"

HRESULT shootingGame::init(void)
{
	//백그라운드 이미지
	IMAGEMANAGER->addImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);
	//ufo 프레임 이밎
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	//공용총알 이미지
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));

	//플레이어 클래스 생성 및 초기화
	_player = new player;
	_player->init();

	//적매니져 클래스 생성 및 초기화
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//플레이어 & 적매니져 클래스 상호참조
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void shootingGame::release(void)
{
	//플레이어 클래스 해제
	SAFE_DELETE(_player);
	//적매니져 클래스 해제
	SAFE_DELETE(_enemyManager);
}

void shootingGame::update(void)
{
	//플레이어 클래스 업데이트
	_player->update();
	//적매니져 클래스 업데이트
	_enemyManager->update();
}

void shootingGame::render(void)
{
	//플레이어 클래스 렌더
	_player->render();
	//적매니져 클래스 렌더
	_enemyManager->render();
}
