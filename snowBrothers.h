#pragma once
#include "gameNode.h"
#include "sb_player.h"
#include "sb_boss.h"
#include "sb_enemy.h"

class snowBrothers : public gameNode
{
private:
	image* _testImage;
	image* _collisionImage;
	image* _enemyCollision;

	sb_player* _sbPlayer;
	sb_boss* _sbBoss;
	sb_enemy* _sbEnemy;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	image* getTestImage() { return _testImage; }
	image* getCollisionImage() { return _collisionImage; }

	snowBrothers() {}
	~snowBrothers() {}
};

