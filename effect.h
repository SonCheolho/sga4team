#pragma once
#include "gameNode.h"

enum FX
{
	//������,
	//�������´�����,
	//�����Ѿ�,
	//ū�Ѿ�,
	������´�����,
	�Ѿ���Ʈ,
	������,
	��������
};

class effect :	public gameNode
{
private:

	FX _eFX;

	struct tagFX
	{
		int fxNumber;//���� : enum FX
		image* fxImage;
		int paturn;//���� -1�̸� �����ݴϴ�.
		int centerX, centerY;
		int width, height;
		int startTime;
		int liveTimer;//0�����϶� ������ -1�� �����մϴ�.
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

