#pragma once
#include "gameNode.h"

class snowBrothers;

#define GRAVITY 0.1f
#define WALK_SPEED 1.5f
#define RUN_SPEED 8.0f
#define JUMP_SPEED 4.5f

enum PLAYER_STATE
{
	IDLE,
	WALK,
	RUN,
	JUMP,
	DROP,
	ATTACK
};

struct tagPlayer
{
	float x, y;
	float speedX, speedY;
	int width, height;
	PLAYER_STATE state;
	int index;
	int count;
	bool isRight;
	bool isJumpDown;
	RECT rc;
	image* img[6];
	int probeX, probeY;
};

class sb_player : public gameNode
{
private:
	tagPlayer _player;
	int _count;
	snowBrothers* _snowBrothers;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void playerMove(void);
	void playerFrame(void);
	void pixelCollision(void);

	sb_player() {}
	~sb_player() {}
};

