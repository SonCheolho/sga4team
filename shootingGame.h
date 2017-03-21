#pragma once
#include "gameNode.h"
#include "player.h"			//�÷��̾� Ŭ���� ����ϱ� ����
#include "enemyManager.h"

class shootingGame : public gameNode
{
private:
	player* _player;	//�÷��̾� Ŭ���� ����
	enemyManager* _enemyManager;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	shootingGame() {}
	~shootingGame() {}
};

