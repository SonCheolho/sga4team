#pragma once
#include "gameNode.h"
/*������ �߰��Ϸ��� ���� ������ϸ� �����Ѵ�*/
#include "sceneTest.h"
#include "shootingGame.h"
#include "loadingScene.h"

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