#pragma once
#include "gameNode.h"
#include "bullets.h"

enum TANKSTATE
{
	WAIT,
	MOVE,
	SHOOTREADY,
	SHOOT,
};

struct tagTank
{
	float x, y;
	float cannonAngle;
	float cannonMaxAngle;
	float cannonMinAngle;
	float tankAngle;
	int frameIndex;
	bool isLeft;
	char* imgKey;
	int count;
	int power;
	TANKSTATE state;
};

class tankManager : public gameNode
{
private:
	vector<tagTank> _vTank;
	vector<tagTank>::iterator _viTank;
	parabolaBullet* _bullet;
public:

	HRESULT init(void);
	void release(void);
	void update(LPCAMERA camera);
	void render(LPCAMERA camera);

	void addTank(char* imgKey, float x, float y);
	image* getTankImg(char* imgKey, TANKSTATE state);

	tankManager(){}
	~tankManager(){}
};

