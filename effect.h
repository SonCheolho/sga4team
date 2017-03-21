#pragma once
#include "gameNode.h"

enum FX
{
	//눈덩이,
	//굴러가는눈덩이,
	//작은총알,
	//큰총알,
	사라지는눈덩이,
	총알히트,
	리스폰,
	보스출혈
};

class effect :	public gameNode
{
private:

	FX _eFX;

	struct tagFX
	{
		int fxNumber;//참조 : enum FX
		image* fxImage;
		int paturn;//패턴 -1이면 지워줍니다.
		int centerX, centerY;
		int width, height;
		int startTime;
		int liveTimer;//0이하일때 패턴을 -1로 세팅합니다.
		RECT rc;
	};

	vector<tagFX> _vFX;
	vector<tagFX>::iterator _viFX;

	vector<tagFX> _vLiveFX;
	vector<tagFX>::iterator _viLiveFX;

public:

	FX getFX() { return _eFX; }
	void createFX(int getEnumFX, int centerX, int centerY, int liveTime);

	void moveFX(int currentTime);

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


	effect() {}
	~effect() {}
};

