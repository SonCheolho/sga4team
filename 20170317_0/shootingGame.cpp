#include "stdafx.h"
#include "shootingGame.h"

HRESULT shootingGame::init(void)
{
	//��׶��� �̹���
	IMAGEMANAGER->addImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);
	//ufo ������ �̓G
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	//�����Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));

	//�÷��̾� Ŭ���� ���� �� �ʱ�ȭ
	_player = new player;
	_player->init();

	//���Ŵ��� Ŭ���� ���� �� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//�÷��̾� & ���Ŵ��� Ŭ���� ��ȣ����
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void shootingGame::release(void)
{
	//�÷��̾� Ŭ���� ����
	SAFE_DELETE(_player);
	//���Ŵ��� Ŭ���� ����
	SAFE_DELETE(_enemyManager);
}

void shootingGame::update(void)
{
	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();
	//���Ŵ��� Ŭ���� ������Ʈ
	_enemyManager->update();
}

void shootingGame::render(void)
{
	//�÷��̾� Ŭ���� ����
	_player->render();
	//���Ŵ��� Ŭ���� ����
	_enemyManager->render();
}
