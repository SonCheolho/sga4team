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
		LEFTSTAY,				//왼쪽 정지
		RIGHTSTAY,				//오른쪽 정지

		LEFTDOWNSTAY,			//왼쪽아래 정지
		RIGHTDOWNSTAY,			//오른쪽아래 정지

		LEFTDOWNJUMP,			//왼쪽아래 점프
		RIGHTDOWNJUMP,			//오른쪽아래 점프

		LEFTRUN,				//왼쪽 달리기
		RIGHTRUN,				//오른쪽 달리기

		LEFTJUMPUP,				//왼쪽 점프업
		RIGHTJUMPUP,			//오른쪽 점프업

		LEFTJUMPDOWN,			//왼쪽 점프다운
		RIGHTJUMPDOWN,			//오른쪽 점프다운

		LEFTMOVEJUMPUP,			//왼쪽이동 점프업
		RIGHTMOVEJUMPUP,		//오른쪽이동 점프업

		LEFTMOVEJUMPDOWN,		//왼쪽이동 점프다운
		RIGHTMOVEJUMPDOWN,		//오른쪽이동 점프다운

		LEFTDASH,				//왼쪽 대쉬
		RIGHTDASH,				//오른쪽 대쉬

		LEFTDASHJUMPUP,			//왼쪽 대쉬 점프업
		RIGHTDASHJUMPUP,		//오른쪽 대쉬 점프업

		LEFTDASHJUMPDOWN,		//왼쪽 대쉬 점프다운
		RIGHTDASHJUMPDOWN,		//오른쪽 대쉬 점프다운

		LEFTDASHMOVEJUMPUP,		//왼쪽이동 점프업
		RIGHTDASHMOVEJUMPUP,	//오른쪽이동 점프업

		LEFTDASHMOVEJUMPDOWN,	//왼쪽이동 점프다운
		RIGHTDASHMOVEJUMPDOWN,	//오른쪽이동 점프다운

		LEFTCATCH,				//왼쪽잡기
		RIGHTCATCH,				//오른쪽잡기

		LEFTCATCHJUMP,			//왼쪽잡고 점프
		RIGHTCATCHJUMP,			//오른쪽잡고 점프

		LEFTLINECATCH,			//왼쪽 라인잡기
		RIGHTLINECATCH,			//오른쪽 라인잡기

		LEFTDOWNLINECATCH,		//왼쪽아래 라인잡기
		RIGHTDOWNLINECATCH,		//오른쪽아래 라인잡기

		LEFTDOWNLINEJUMP,		//왼쪽아래 라인점프
		RIGHTDOWNLINEJUMP,		//오른쪽아래 라인점프

		LEFTMOVELINECATCH,		//왼쪽이동 라인잡기
		RIGHTMOVELINECATCH,		//오른쪽이동 라인잡기

		LEFTLINEUPSTAY,			//왼쪽라인위 정지
		RIGHTLINEUPSTAY,		//오른쪽라인위 정지

		LEFTDOWNLINEUPSTAY,		//왼쪽아래라인위 정지
		RIGHTDOWNLINEUPSTAY,	//오른쪽아래라인위 정지

		LEFTMOVELINEUP,			//왼쪽라인위 이동
		RIGHTMOVELINEUP,		//오른쪽자인위 이동

		LEFTDOWNLINEUPJUMP,		//왼쪽아래라인위 점프
		RIGHTDOWNLINEUPJUMP		//오른쪽아래라인위 점프
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
	//렉트 충돌
	void megamanCollision();
	//픽셀 충돌
	void megamanPixelCollision();
	void megamanDrawImage(HDC hdc);

	bool intersectLineRect(LPPOINT point1, LPPOINT point2, LPRECT rc);

	megamanX6();
	~megamanX6();
};

