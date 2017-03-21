#pragma once
#include "gameNode.h"
#include "megamanX6.h"
#include "fortress.h"

class mainGame :public gameNode
{
private:
	megamanX6* _megamanX6;
	fortress* _fortress;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame();
	~mainGame();
};

