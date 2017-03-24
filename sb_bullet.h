#pragma once
#include "gameNode.h"

#define NORMAL_BULLET_SPEEDX 5.0f
#define NORMAL_BULLET_SPEEDY 5.0f
#define NORMAL_BULLET_GRAVITY 0.2f;

enum bulletType
{
	NORMAL,
	POWER_UP,
	RANGE_UP,
	FULL_UP
};

struct tagBullet
{
	image* bulletImg[2];
	float x, y;
	float speedX, speedY;
	int width, height;
	float fireX, fireY;
	float angle;
	float gravity;
	bool fire;
	int count;
	int index;
};

class sb_bullet : public gameNode
{
private:

	




public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sb_bullet() {}
	~sb_bullet(){}
};

