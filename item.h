#pragma once
#include "gameNode.h"

enum ITEM
{
	�ʹ�1,
	�ʹ�2,
	�ʹ�3,
	�ʹ�4,
	�ʹ�5,
	�ʹ�6,
	�ʹ�7,
	�ʹ�8,
	�ʹ�9,
	�ʹ�10,
	��������,
	�������,
	�ʷϹ���,
	�Ķ�����,
	���ʽ�1,
	���ʽ�2
};

class item : public gameNode
{
private:

	//������ ����ü
	struct tagItem
	{
		int itemNumber;//���� : enum ITEM
		image* itemImage;
		int paturn;
		int point;
		int centerX, centerY;
		int width, height;
		int liveTimer;//���� -1�̸� �����ݴϴ�. -1�϶� �ش� ������ ������ �̿��� ��� ó���� �����մϴ�.[�߿�]
		//�÷��̾�� �浹�� �߻� �� ��� ������ -1�� ������ �ݴϴ�.(������ ����� ������ �浹�Լ� ���鿹��)
		RECT rc;
	};
	
	//�����۸������ ���� �� ���ͷ�����
	vector<tagItem> _vItemList;
	vector<tagItem>::iterator _viItemList;

	//�� ���� ������ ���� �� ���ͷ�����
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

public:

	//
	vector<tagItem> getVItem() { return _vItem; }
	//

	void itemSetting(int itemNumber, int point);//������������ ����ֱ� ���� �����Լ�(init���� ���)

	int findItemList(int itemNumber);

	void createItem(int itemNumber, int centerX, int centerY);//�������� ���ϴ� ��ġ�� ����
	void createBonusItem(int maxItem);//���ʽ� �������� ����(�Ͼ��� ���ʽ�������)

	void moveBonusItem(HDC dc, int speed);//���ʽ��������� �������� ������ ����
	void moveItem();//���̺� ī��Ʈ�� �ٿ��ϰ� �����ش�.(���ʽ� ������ ����)

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	item() {}
	~item() {}
};

