#pragma once
#include "gameNode.h"
//==================================================================
//		## bullets ## (�Ѿ�, �̻��� Ŭ����)
//==================================================================
//�Ѿ� ����ü
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float radius;
	float speedX;
	float speedY;
	float angle;
	bool fire;
	int count;
};

//==================================================================
//		## bullet ## �����Ѿ� (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
class bullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	char* _imageName;	//�Ѿ��̹��� �̸�
	float _range;		//��Ÿ�
	float _bulletMax;	//�Ѿ� �ִ� ����

public:
	//�Ѿ��̹����̸�, �Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻� (�Ѿ���ġ, ����, �ӵ�)
	void fire(float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move(void);

	bullet() {}
	~bullet() {}
};

//==================================================================
//		## missile ## (missile[10] => �迭ó�� �̸������صΰ� �Ѿ˹߻�)
//==================================================================
class missile : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;	//��Ÿ�

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move(void);

	missile() {}
	~missile() {}
};

//==================================================================
//		## missileM1 ## (�򶧸��� �ѹ߾� �����ؼ� �߻� - �ڵ�����)
//==================================================================
class missileM1 : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;		//��Ÿ�
	float _bulletMax;	//�Ѿ� �ִ� ����

public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	//�Ѿ˹߻�
	void fire(float x, float y);
	//�Ѿ˹���
	void move(void);

	missileM1() {}
	~missileM1() {}
};

//==================================================================
//		## parabolaBullet ## (������ źȯ)
//==================================================================
class parabolaBullet : public gameNode
{
private:
	//�Ѿ� ����ü�� ���� ����, �ݺ���
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;
public:
	//�Ѿ˰���, �Ѿ˻�Ÿ��� �ʱ�ȭ
	HRESULT init(void);
	void release(void);
	void update(LPCAMERA camera);
	void render(LPCAMERA camera);

	//�Ѿ˹߻�
	void fire(char* imageName, float x, float y, float angle, float speed);
	//�Ѿ˹���
	void move(LPCAMERA camera);

	parabolaBullet() {}
	~parabolaBullet() {}
};