#pragma once
//====================================================================
//			## image ## (앞으로 계속 업데이트 된다)
//====================================================================
class image
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,		//리소스로 로딩
		LOAD_FILE,				//파일로 로딩 (주 사용)
		LOAD_EMPTY,				//빈비트맵 로딩
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD		resID;			//리소스 ID
		HDC			hMemDC;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드비트맵
		float		x;				//이미지 x좌표
		float		y;				//이미지 y좌표
		int			width;			//이미기 가로크기
		int			height;			//이미지 세로크기
		int			currentFrameX;	//현재 프레임 x
		int			currentFrameY;	//현재 프레임 y
		int			maxFrameX;		//최대 x프레임
		int			maxFrameY;		//최대 y프레임
		int			frameWidth;		//1프레임 가로길이
		int			frameHeight;	//1프레임 세로길이
		BYTE		loadType;		//이미지 로드타입

		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	CHAR*			_fileName;		//이미지 이름
	BOOL			_isTrans;		//배경색 없앨꺼냐? (마젠타)
	COLORREF		_transColor;	//배경색 없앨 RGB(255, 0, 255)

	LPIMAGE_INFO	_blendImage;	//알파블렌드 이미지
	BLENDFUNCTION	_blendFunc;		//알파블렌드 기능

public:
	image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _transColor(RGB(0, 0, 0)), _blendImage(NULL) {}
	~image() {}
//====================================================================
//			## 초기화 ##
//====================================================================
	//빈 비트맵으로 초기화
	HRESULT init(int width, int height);
	//이미지 리소스로 초기화 (사용안함)
	HRESULT init(const DWORD resID, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//이미지 파일로 초기화 (주 사용)
	HRESULT init(const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//프레임이미지 파일로 초기화 (주 사용)
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//알파블렌드 초기화
	HRESULT initForAlphaBlend(void);

//====================================================================
//			## 해제 ##
//====================================================================
	void release(void);

//====================================================================
//			## 일반렌더 ##
//====================================================================
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//====================================================================
//			## 알파렌더 ##
//====================================================================
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//====================================================================
//			## 프레임렌더 ##
//====================================================================
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//====================================================================
//			## 루프렌더 ##
//====================================================================
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

//====================================================================
//			## 인라인 함수 ## (겟터, 셋터)
//====================================================================
	inline HDC getMemDC(void) { return _imageInfo->hMemDC; }

	//이미지 x좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	//이미지 y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }
	//이미지 가로, 세로크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	//바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->width,
			(int)_imageInfo->y + _imageInfo->height };

		return rc;
	}
	inline RECT boundingBoxWithFrame(void)
	{
		RECT rc = { (int)_imageInfo->x, (int)_imageInfo->y,
			(int)_imageInfo->x + _imageInfo->frameWidth,
			(int)_imageInfo->y + _imageInfo->frameHeight };

		return rc;
	}

	//프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrmaeX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}
	//프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrmaeY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//이미지 1프레임 가로, 세로길이
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
	//맥스프레임 x, y
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrmaeY(void) { return _imageInfo->maxFrameY; }
};

