#pragma once
#include "gameNode.h"

#define GRAVITY 0.4f
#define MAX_DASH_TIME 20
#define RUN_SPEED 5.0f
#define DASH_SPEED 8.0f
#define JUMP_SPEED 9.0f
#define DASH_JUMP_SPEED 9.0f

class megamanX6 : public gameNode
{
public:
	enum MEGAMAN_STATUS
	{
		STAY,
		DOWNSTAY,
		DOWNJUMP,
		RUN,
		JUMPUP,
		JUMPDOWN,
		MOVEJUMPUP,
		MOVEJUMPDOWN,
		DASH,
		DASHJUMPUP,
		DASHJUMPDOWN,
		DASHMOVEJUMPUP,
		DASHMOVEJUMPDOWN,
		CATCH,
		CATCHJUMP,
		LINECATCH,
		DOWNLINECATCH,
		DOWNLINEJUMP,
		MOVELINECATCH,
		LINEUPSTAY,
		DOWNLINEUPSTAY,
		MOVELINEUP,
		DOWNLINEUPJUMP

		/*
		LEFTSTAY,				//���� ����
		RIGHTSTAY,				//������ ����

		LEFTDOWNSTAY,			//���ʾƷ� ����
		RIGHTDOWNSTAY,			//�����ʾƷ� ����

		LEFTDOWNJUMP,			//���ʾƷ� ����
		RIGHTDOWNJUMP,			//�����ʾƷ� ����

		LEFTRUN,				//���� �޸���
		RIGHTRUN,				//������ �޸���

		LEFTJUMPUP,				//���� ������
		RIGHTJUMPUP,			//������ ������

		LEFTJUMPDOWN,			//���� �����ٿ�
		RIGHTJUMPDOWN,			//������ �����ٿ�

		LEFTMOVEJUMPUP,			//�����̵� ������
		RIGHTMOVEJUMPUP,		//�������̵� ������

		LEFTMOVEJUMPDOWN,		//�����̵� �����ٿ�
		RIGHTMOVEJUMPDOWN,		//�������̵� �����ٿ�

		LEFTDASH,				//���� �뽬
		RIGHTDASH,				//������ �뽬

		LEFTDASHJUMPUP,			//���� �뽬 ������
		RIGHTDASHJUMPUP,		//������ �뽬 ������

		LEFTDASHJUMPDOWN,		//���� �뽬 �����ٿ�
		RIGHTDASHJUMPDOWN,		//������ �뽬 �����ٿ�

		LEFTDASHMOVEJUMPUP,		//�����̵� ������
		RIGHTDASHMOVEJUMPUP,	//�������̵� ������

		LEFTDASHMOVEJUMPDOWN,	//�����̵� �����ٿ�
		RIGHTDASHMOVEJUMPDOWN,	//�������̵� �����ٿ�

		LEFTCATCH,				//�������
		RIGHTCATCH,				//���������

		LEFTCATCHJUMP,			//������� ����
		RIGHTCATCHJUMP,			//��������� ����

		LEFTLINECATCH,			//���� �������
		RIGHTLINECATCH,			//������ �������

		LEFTDOWNLINECATCH,		//���ʾƷ� �������
		RIGHTDOWNLINECATCH,		//�����ʾƷ� �������

		LEFTDOWNLINEJUMP,		//���ʾƷ� ��������
		RIGHTDOWNLINEJUMP,		//�����ʾƷ� ��������

		LEFTMOVELINECATCH,		//�����̵� �������
		RIGHTMOVELINECATCH,		//�������̵� �������

		LEFTLINEUPSTAY,			//���ʶ����� ����
		RIGHTLINEUPSTAY,		//�����ʶ����� ����

		LEFTDOWNLINEUPSTAY,		//���ʾƷ������� ����
		RIGHTDOWNLINEUPSTAY,	//�����ʾƷ������� ����

		LEFTMOVELINEUP,			//���ʶ����� �̵�
		RIGHTMOVELINEUP,		//������������ �̵�

		LEFTDOWNLINEUPJUMP,		//���ʾƷ������� ����
		RIGHTDOWNLINEUPJUMP		//�����ʾƷ������� ����
		*/
	};

	struct tagMegaman
	{
		float x, y;
		float speedX, speedY;
		int width, height;
		MEGAMAN_STATUS status;
		int dashTimer;
		int frameIndex;
		bool isLeft;
		RECT rc;
	};

	struct tagObject
	{
		bool isOverlap;
		bool isSideCatch;
		bool isUpper;
		bool isLine;
		bool isLineCatch;
		POINT point[2];
	};

	struct tagWall : tagObject
	{
		tagWall(int left, int top, int right, int bottom, bool idOverlap, bool isSideCatch, bool isUpper)
		{
			tagObject::isOverlap = idOverlap;
			tagObject::isSideCatch = isSideCatch;
			tagObject::isUpper = isUpper;
			tagObject::isLine = false;
			tagObject::point[0].x = left;
			tagObject::point[0].y = top;
			tagObject::point[1].x = right;
			tagObject::point[1].y = bottom;
		}
	};

	struct tagLine : tagObject
	{
		tagLine(int x1, int y1, int x2, int y2, bool isUpper, bool isLineCatch)
		{
			tagObject::isOverlap = true;
			tagObject::isSideCatch = false;
			tagObject::isUpper = isUpper;
			tagObject::isLine = true;
			tagObject::isLineCatch = isLineCatch;
			tagObject::point[0].x = x1;
			tagObject::point[0].y = y1;
			tagObject::point[1].x = x2;
			tagObject::point[1].y = y2;
		}
	};
private:
	int _count;
	image* _bgImage;
	image* _mapImage;
	image* _minimapImage;
	image* _megamanImage[7];

	tagMegaman _megaman;
	CAMERA _camera;
	vector<tagObject> _vObject;
	map<string, COLORREF> _pixelMap;
public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void megamanMove();
	//��Ʈ �浹
	void megamanCollision();
	//�ȼ� �浹
	void megamanPixelCollision();
	void megamanDrawImage(HDC hdc);

	bool intersectLineRect(LPPOINT point1, LPPOINT point2, LPRECT rc);

	megamanX6();
	~megamanX6();
};

