#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"

//���Ŵ����� ��ȣ�����ϱ� ���ؼ� Ŭ���� ���漱��
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;			//�÷��̾�(����) �̹���
	float _x, _y;
	RECT _rc;

	missile* _missile;		//�̻��� Ŭ����
	missileM1* _missileM1;	//�̻���m1 Ŭ����

	enemyManager* _em;		//�����Ҵ� �ϸ� ���� �ȵȴ�!! (�޸� ���� ������� ��)
	
	progressBar* _hpBar;	//ü�¹�
	float _maxHp, _currentHp;//�ִ�ü��, ����ü��

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̻���M1 ����
	void removeMissileM1(int index);

	//�浹�Լ� (�÷��̾� �Ѿ��̶� ���Ŵ��� �̴Ͼ�)
	void collision(void);

	//������
	void hitDamage(float damage);

	//�÷��̾� �̹��� ��������
	image* getRocketImage() { return _rocket; }

	//�̻���M1 Ŭ���� ��������
	missileM1* getMissileM1() { return _missileM1; }

	//��ȣ������ ���Ŵ��������͸� �ѱ� �����Լ�
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

