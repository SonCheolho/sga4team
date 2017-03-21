#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//적매니저와 상호참조하기 위해서 클래스 전방선언
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;			//플레이어(로켓) 이미지
	float _x, _y;
	RECT _rc;

	missile* _missile;		//미사일 클래스
	missileM1* _missileM1;	//미사일m1 클래스

	enemyManager* _em;		//동적할당 하면 절대 안된다!! (메모리 공유 시켜줘야 함)
	
	progressBar* _hpBar;	//체력바
	float _maxHp, _currentHp;//최대체력, 현재체력

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//미사일M1 삭제
	void removeMissileM1(int index);

	//충돌함수 (플레이어 총알이랑 적매니져 미니언)
	void collision(void);

	//피통깎기
	void hitDamage(float damage);

	//플레이어 이미지 가져오기
	image* getRocketImage() { return _rocket; }

	//미사일M1 클래스 가져오기
	missileM1* getMissileM1() { return _missileM1; }

	//상호참조시 적매니져포인터를 넘길 셋터함수
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

