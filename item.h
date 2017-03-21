#pragma once
#include "gameNode.h"

enum ITEM
{
	초밥1,
	초밥2,
	초밥3,
	초밥4,
	초밥5,
	초밥6,
	초밥7,
	초밥8,
	초밥9,
	초밥10,
	빨간물약,
	노란물약,
	초록물약,
	파란물약,
	보너스1,
	보너스2
};

class item : public gameNode
{
private:

	//아이템 구조체
	struct tagItem
	{
		int itemNumber;//참조 : enum ITEM
		image* itemImage;
		int paturn;
		int point;
		int centerX, centerY;
		int width, height;
		int liveTimer;//패턴 -1이면 지워줍니다. -1일때 해당 아이템 지워줌 이외의 모든 처리를 금지합니다.[중요]
		//플레이어와 충돌이 발생 할 경우 패턴을 -1로 세팅해 줍니다.(아이템 담당이 아이템 충돌함수 만들예정)
		RECT rc;
	};
	
	//아이템목록정의 백터 및 이터레이터
	vector<tagItem> _vItemList;
	vector<tagItem>::iterator _viItemList;

	//인 게임 아이템 백터 및 이터레이터
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

public:

	//
	vector<tagItem> getVItem() { return _vItem; }
	//

	void itemSetting(int itemNumber, int point);//아이템정보를 담아주기 위한 세팅함수(init에서 사용)

	int findItemList(int itemNumber);

	void createItem(int itemNumber, int centerX, int centerY);//아이템을 원하는 위치에 생성
	void createBonusItem(int maxItem);//보너스 아이템을 생성(싹쓸이 보너스아이템)

	void moveBonusItem(HDC dc, int speed);//보너스아이템이 떨어지는 움직임 진행
	void moveItem();//라이브 카운트를 다운하고 지워준다.(보너스 아이템 포함)

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	item() {}
	~item() {}
};

