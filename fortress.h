#pragma once
#include "gameNode.h"
#include "tank.h"

class fortress : public gameNode
{
private:
	image* _backImg;
	image* _mapImg;
	image* _miniMapImg;
	tankManager* _tankManager;
	CAMERA _camera;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	fortress(){}
	~fortress(){}
};

