#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"

//��ȣ������ �÷��̾� Ŭ���� ���漱��
class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;	//�̴Ͼ� ����
	vector<enemy*>::iterator _viMinion;

	bullet* _bullet;			//�����Ѿ�

	player* _pl;				//�����Ҵ� ���� �ϸ� �ȵȴ�

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� -> �ʱ�ȭ�� �ֱ�
	void setMinion(void);
	//�̴Ͼ� �Ѿ� �߻�
	void minionBulletFire(void);

	//�̴Ͼ� ����
	void removeMinion(int index);

	//�浹�Լ�
	void collision(void);

	//�̴Ͼ��� ��������
	vector<enemy*> getVMinion() { return _vMinion; }
	
	//��ȣ������ �÷��̾������͸� �ѱ� �����Լ�
	void setPlayerLink(player* pl) { _pl = pl; }

	enemyManager() {}
	~enemyManager() {}
};

