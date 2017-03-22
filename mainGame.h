#pragma once
#include "gameNode.h"
/*앞으로 추가하려는 씬의 헤더파일만 선언한다*/
#include "sceneTest.h"
#include "shootingGame.h"
#include "loadingScene.h"
#include "snowBrothers.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	mainGame() {}
	~mainGame() {}
};