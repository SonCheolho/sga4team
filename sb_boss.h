#pragma once
#include "gameNode.h"
class sb_boss :	public gameNode
{
private:
	image* _bossImage;
	image* _bossEffectImage;

	RECT _bosseffect;
	RECT _bossRc;

	int _bossindex;
	int _EffectIndex;
	int _count;
	
	bool fire;
	bool start;

	POINT _BossPoint;
	int _MoveY;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sb_boss() {}
	~sb_boss() {}
};

