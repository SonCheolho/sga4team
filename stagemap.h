#pragma once
#include "gameNode.h"

enum stageNum
{
	stage1,
	stage2,
	stage3,
	stage4,
	stage5,
	stage6,
	stage7,
	stage8,
	stage9,
	stage10
};
class stagemap : public gameNode
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	stagemap() {}
	~stagemap() {}
};

