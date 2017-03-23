#pragma once
#include "gameNode.h"
enum LOOK
{
	좌,
	우,
	상,
	하,
	정지
};
enum ENEMY_NUMBER
{
	적1,
	적2,
	적3
};
enum MOTION
{
	리스폰,
	대기,
	점프,
	걷기,
	피격,
	피격해제,
	죽음,
	특수1,
	특수2,
	공격1,
	공격2,
	흰눈뭉치,
	파란눈뭉치
};

class sb_enemy : public gameNode
{
private:

	//에너미 구조체
	struct tagEnemy
	{
		//에너미 정보
		int enemyNumber;
		int look;
		int motion;
		int motionTimer;
		int paturn;
		int hitCount;// ::눈뭉치 쌓이는 파라메터
		int def;// ::눈뭉치 쌓이는 수치를 감소시키는 변수
		bool isShoot;// :: 눈뭉치 상태일때 플레이어에게 굴려졌는가?
		//에너미 위치 및 크기 정보
		int centerX, centerY;
		int width, height;
		RECT rc;
	};

	//에너미 인게임 할당 벡터 생성
	vector<tagEnemy> _vEnemy;
	vector<tagEnemy>::iterator _viEnemy;


public:

	//에너미 초기화
	void enemySet(ENEMY_NUMBER EenemyNum, LOOK currentLook, int centerX, int centerY, int def);

	//에너미 무빙
	void enemyMoving();
	//눈뭉치 구를 때
	void snowBallMoving();

	//픽셀 충돌
	void pixelCollision();

	//겟셋
	vector<tagEnemy> get_vEnemy() { return _vEnemy; }

	void setIsShoot(int index) { _vEnemy[index].isShoot = true; }


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sb_enemy() {}
	~sb_enemy() {}
};

