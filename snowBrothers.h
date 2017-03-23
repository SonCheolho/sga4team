#pragma once
#include "gameNode.h"
#include "sb_player.h"

class snowBrothers : public gameNode
{
private:
	image* _testImage;
	image* _collisionImage;

	sb_player* _sbPlayer;

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

