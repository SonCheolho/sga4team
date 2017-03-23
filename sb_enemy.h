#pragma once
#include "gameNode.h"
enum LOOK
{
	��,
	��,
	��,
	��,
	����
};
enum ENEMY_NUMBER
{
	��1,
	��2,
	��3
};
enum MOTION
{
	������,
	���,
	����,
	�ȱ�,
	�ǰ�,
	�ǰ�����,
	����,
	Ư��1,
	Ư��2,
	����1,
	����2,
	�򴫹�ġ,
	�Ķ�����ġ
};

class sb_enemy : public gameNode
{
private:

	//���ʹ� ����ü
	struct tagEnemy
	{
		//���ʹ� ����
		int enemyNumber;
		int look;
		int motion;
		int motionTimer;
		int paturn;
		int hitCount;// ::����ġ ���̴� �Ķ����
		int def;// ::����ġ ���̴� ��ġ�� ���ҽ�Ű�� ����
		bool isShoot;// :: ����ġ �����϶� �÷��̾�� �������°�?
		//���ʹ� ��ġ �� ũ�� ����
		int centerX, centerY;
		int width, height;
		RECT rc;
	};

	//���ʹ� �ΰ��� �Ҵ� ���� ����
	vector<tagEnemy> _vEnemy;
	vector<tagEnemy>::iterator _viEnemy;


public:

	//���ʹ� �ʱ�ȭ
	void enemySet(ENEMY_NUMBER EenemyNum, LOOK currentLook, int centerX, int centerY, int def);

	//���ʹ� ����
	void enemyMoving();
	//����ġ ���� ��
	void snowBallMoving();

	//�ȼ� �浹
	void pixelCollision();

	//�ټ�
	vector<tagEnemy> get_vEnemy() { return _vEnemy; }

	void setIsShoot(int index) { _vEnemy[index].isShoot = true; }


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	sb_enemy() {}
	~sb_enemy() {}
};

