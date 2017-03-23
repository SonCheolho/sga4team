#pragma once
#include "gameNode.h"
class sb_bullet : public gameNode
{
private:

	struct tagBullet
	{
		
	};




public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	sb_bullet() {}
	~sb_bullet(){}
};

