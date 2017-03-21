#include "stdafx.h"
#include "megamanX6.h"


megamanX6::megamanX6()
{
}

megamanX6::~megamanX6()
{
}

HRESULT megamanX6::init(void)
{
	IMAGEMANAGER->addImage("충돌 픽셀", "./image/background_collision_5000_864.bmp", 5000, 864, true, RGB(255, 255, 255));

	_bgImage = new image;
	_bgImage->init("./image/gameboy_1000_800.bmp", 1000, 800, true, RGB(255, 0, 255));

	_mapImage = new image;
	_mapImage->init("./image/background_5000_864.bmp", 5000, 864);

	_minimapImage = new image;
	_minimapImage->init("./image/background_5000_864.bmp", 500, 86);

	_megamanImage[0] = new image;
	_megamanImage[0]->init("./image/megaman_shadow_nomal_190_96.bmp", 190, 96, 5, 2, true, RGB(255, 0, 255));

	_megamanImage[1] = new image;
	_megamanImage[1]->init("./image/megaman_shadow_run_672_98.bmp", 672, 98, 14, 2, true, RGB(255, 0, 255));

	_megamanImage[2] = new image;
	_megamanImage[2]->init("./image/megaman_shadow_jump_304_116.bmp", 304, 116, 8, 2, true, RGB(255, 0, 255));

	_megamanImage[3] = new image;
	_megamanImage[3]->init("./image/megaman_shadow_catch_68_116.bmp", 68, 116, 2, 2, true, RGB(255, 0, 255));

	_megamanImage[4] = new image;
	_megamanImage[4]->init("./image/megaman_shadow_dash_232_96.bmp", 232, 96, 4, 2, true, RGB(255, 0, 255));

	_megamanImage[5] = new image;
	_megamanImage[5]->init("./image/megaman_shadow_linecatch_32_136.bmp", 32, 136, 1, 2, true, RGB(255, 0, 255));

	_megamanImage[6] = new image;
	_megamanImage[6]->init("./image/megaman_shadow_down_42_68.bmp", 40, 68, 1, 2, true, RGB(255, 0, 255));

	_megaman.x = 20;
	_megaman.y = 700;
	_megaman.width = 38;
	_megaman.height = 48;
	_megaman.speedX = 0;
	_megaman.speedY = 0;
	_megaman.isLeft = false;
	_megaman.status = STAY;
	_megaman.dashTimer = 0;
	_megaman.frameIndex = 0;
	_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);

	_camera.marginX = 100;
	_camera.marginY = 200;
	_camera.mapWidth = 5000;
	_camera.mapHeight = 864;
	_camera.viewStartX = 0;
	_camera.viewStartY = 364;
	_camera.viewWidth = 800;
	_camera.viewHeight = 500;
	_camera.switchViewDelay = 0;

	//바닥
	_vObject.push_back(tagWall(0, 830, 704, 864, false, true, true));
	_vObject.push_back(tagWall(768, 830, 1824, 864, false, true, true));
	_vObject.push_back(tagWall(1952, 830, 2176, 864, false, true, true));
	_vObject.push_back(tagWall(2240, 830, 2432, 864, false, true, true));
	_vObject.push_back(tagWall(2496, 830, 2944, 864, false, true, true));
	_vObject.push_back(tagWall(3008, 830, 5000, 864, false, true, true));

	//뒷배경 오브젝트
	_vObject.push_back(tagWall(322, 705, 384, 864, true, true, true));
	_vObject.push_back(tagWall(450, 575, 602, 864, true, true, true));
	_vObject.push_back(tagWall(354, 736, 541, 864, true, true, true));
	_vObject.push_back(tagWall(930, 545, 1052, 864, true, true, true));
	_vObject.push_back(tagWall(994, 736, 1118, 864, true, true, true));
	_vObject.push_back(tagWall(1538, 736, 1790, 864, true, true, true));
	_vObject.push_back(tagWall(1602, 672, 1725, 736, true, true, true));
	_vObject.push_back(tagWall(2562, 736, 2684, 864, true, true, true));
	_vObject.push_back(tagWall(2594, 608, 2654, 736, true, true, true));
	_vObject.push_back(tagWall(3170, 672, 3260, 864, true, true, true));
	_vObject.push_back(tagWall(3234, 736, 3358, 864, true, true, true));

	//고체 오브젝트
	_vObject.push_back(tagWall(64, 703, 96, 864, false, true, true));
	_vObject.push_back(tagWall(64, 543, 96, 576, false, true, true));
	_vObject.push_back(tagWall(1248, 607, 1408, 703, false, true, true));
	_vObject.push_back(tagWall(1312, 799, 1344, 830, false, true, true));
	_vObject.push_back(tagWall(1952, 799, 1984, 830, false, true, true));
	_vObject.push_back(tagWall(2144, 799, 2176, 830, false, true, true));
	_vObject.push_back(tagWall(2305, 703, 2366, 864, false, true, true));
	_vObject.push_back(tagWall(2496, 799, 2528, 830, false, true, true));
	_vObject.push_back(tagWall(2720, 672, 2752, 703, false, true, true));
	_vObject.push_back(tagWall(2720, 703, 2944, 735, false, true, true));
	_vObject.push_back(tagWall(2783, 511, 2816, 543, false, true, true));
	_vObject.push_back(tagWall(2783, 543, 2912, 576, false, true, true));
	_vObject.push_back(tagWall(2783, 96, 2816, 128, false, true, true));
	_vObject.push_back(tagWall(2880, 511, 2912, 543, false, true, true));
	_vObject.push_back(tagWall(2914, 672, 2944, 703, false, true, true));
	_vObject.push_back(tagWall(2912, 799, 2944, 830, false, true, true));
	_vObject.push_back(tagWall(3073, 735, 3134, 864, false, true, true));
	_vObject.push_back(tagWall(3457, 703, 3518, 864, false, true, true));
	_vObject.push_back(tagWall(3648, 735, 3680, 767, false, true, true));
	_vObject.push_back(tagWall(3648, 767, 4064, 830, false, true, true));
	_vObject.push_back(tagWall(3776, 671, 3808, 703, false, true, true));
	_vObject.push_back(tagWall(3776, 703, 4064, 767, false, true, true));
	_vObject.push_back(tagWall(3904, 607, 3936, 639, false, true, true));
	_vObject.push_back(tagWall(4032, 607, 4064, 639, false, true, true));
	_vObject.push_back(tagWall(3904, 639, 4064, 703, false, true, true));

	//덩쿨(사다리 - 미완성이라 뒷배경형식으로)
	_vObject.push_back(tagWall(2783, 128, 2816, 511, true, true, true));
	
	//구름
	_vObject.push_back(tagWall(1568, 255, 2368, 288, false, true, true));
	_vObject.push_back(tagWall(2368, 159, 2431, 192, false, true, true));
	_vObject.push_back(tagWall(2431, 255, 2496, 288, false, true, true));
	_vObject.push_back(tagWall(2559, 223, 2624, 256, false, true, true));
	_vObject.push_back(tagWall(2687, 192, 2783, 224, false, true, true));
	_vObject.push_back(tagWall(3103, 383, 3328, 416, false, true, true));

	//줄오브젝트
	_vObject.push_back(tagLine(179, 475, 562, 475, true, true));
	_vObject.push_back(tagLine(616, 475, 963, 312, true, true));
	_vObject.push_back(tagLine(1032, 316, 1378, 478, false, true));

	_pixelMap.insert(make_pair("빈공간", RGB(255, 255, 255)));
	_pixelMap.insert(make_pair("잡기o/통과x", RGB(255, 0, 255)));
	_pixelMap.insert(make_pair("통과되는벽1", RGB(0, 255, 255)));
	_pixelMap.insert(make_pair("통과되는벽2", RGB(0, 255, 0)));
	_pixelMap.insert(make_pair("왼쪽에서잡기가능", RGB(0, 0, 255)));
	_pixelMap.insert(make_pair("오른쪽에서잡기가능", RGB(255, 255, 0)));
	_pixelMap.insert(make_pair("줄(잡기&위에서기)", RGB(255, 0, 0)));

	_count = 0;
	return S_OK;
}
void megamanX6::release(void)
{
	_mapImage->release();
	SAFE_DELETE(_mapImage);
	for (int i = 0; i < 7;i++)
	{
		_megamanImage[i]->release();
		SAFE_DELETE(_megamanImage[i]);
	}
}
void megamanX6::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_megaman.status != DASH
			&& _megaman.status != DASHJUMPUP
			&& _megaman.status != DASHMOVEJUMPUP
			&& _megaman.status != DASHJUMPDOWN
			&& _megaman.status != DASHMOVEJUMPDOWN)
		{
			if (_megaman.status == STAY
				|| _megaman.status == DOWNSTAY
				|| _megaman.status == RUN)
			{
				if (!(_megaman.isLeft && _megaman.status == RUN)) _megaman.frameIndex = _megamanImage[1]->getMaxFrameX();
				_megaman.status = RUN;
				_megaman.dashTimer = 0;
			}
			else if (_megaman.status == JUMPUP)
			{
				_megaman.status = MOVEJUMPUP;
			}
			else if (_megaman.status == JUMPDOWN)
			{
				_megaman.status = MOVEJUMPDOWN;
			}
			else if (_megaman.status == LINECATCH || _megaman.status == MOVELINECATCH)
			{
				_megaman.status = MOVELINECATCH;
			}
			else if (_megaman.status == LINEUPSTAY
				|| _megaman.status == MOVELINEUP
				|| _megaman.status == DOWNLINEUPSTAY)
			{
				_megaman.status = MOVELINEUP;
			}
			_megaman.speedX = RUN_SPEED;
		}
		else
		{
			if (!_megaman.isLeft && _megaman.status == DASH)
			{
				_megaman.frameIndex = 0;
				_megaman.status = RUN;
				_megaman.dashTimer = 0;
				_megaman.speedX = RUN_SPEED;
			}
			else if (_megaman.status == DASHJUMPUP)
			{
				_megaman.status = DASHMOVEJUMPUP;
			}
			else if (_megaman.status == DASHJUMPDOWN)
			{
				_megaman.status = DASHMOVEJUMPDOWN;
			}

			if (_megaman.status == DASHMOVEJUMPUP || _megaman.status == DASHMOVEJUMPDOWN)
			{
				_megaman.speedX = DASH_SPEED;
			}
		}
		_megaman.isLeft = true;
	}
	else if (_megaman.isLeft && (_megaman.status == RUN || _megaman.status == CATCH))
	{
		_megaman.frameIndex = _megamanImage[0]->getMaxFrameX();
		_megaman.status = STAY;
		_megaman.speedX = 0.0f;
	}
	else if (_megaman.isLeft
		&& (_megaman.status == MOVEJUMPUP
		|| _megaman.status == MOVEJUMPDOWN
		|| _megaman.status == DASHMOVEJUMPUP
		|| _megaman.status == DASHMOVEJUMPDOWN))
	{
		_megaman.speedX = 0.0f;
		if (_megaman.status == MOVEJUMPUP) _megaman.status = JUMPUP;
		else if (_megaman.status == MOVEJUMPDOWN) _megaman.status = JUMPDOWN;
		else if (_megaman.status == DASHMOVEJUMPUP) _megaman.status = DASHJUMPUP;
		else if (_megaman.status == DASHMOVEJUMPDOWN) _megaman.status = DASHJUMPDOWN;
	}
	else if (_megaman.isLeft && _megaman.status == MOVELINECATCH)
	{
		_megaman.speedX = 0.0f;
		_megaman.status = LINECATCH;
	}
	else if (_megaman.isLeft && _megaman.status == MOVELINEUP)
	{
		_megaman.speedX = 0.0f;
		_megaman.status = LINEUPSTAY;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_megaman.status != DASH
			&& _megaman.status != DASHJUMPUP
			&& _megaman.status != DASHMOVEJUMPUP
			&& _megaman.status != DASHJUMPDOWN
			&& _megaman.status != DASHMOVEJUMPDOWN)
		{
			if (_megaman.status == STAY
				|| _megaman.status == DOWNSTAY
				|| _megaman.status == RUN)
			{
				if (!(!_megaman.isLeft && _megaman.status == RUN)) _megaman.frameIndex = 0;
				_megaman.status = RUN;
				_megaman.dashTimer = 0;
			}
			else if (_megaman.status == JUMPUP)
			{
				_megaman.status = MOVEJUMPUP;
			}
			else if (_megaman.status == JUMPDOWN)
			{
				_megaman.status = MOVEJUMPDOWN;
			}
			else if (_megaman.status == LINECATCH
				|| _megaman.status == MOVELINECATCH)
			{
				_megaman.status = MOVELINECATCH;
			}
			else if (_megaman.status == LINEUPSTAY
				|| _megaman.status == MOVELINEUP
				|| _megaman.status == DOWNLINEUPSTAY)
			{
				_megaman.status = MOVELINEUP;
			}
			_megaman.speedX = RUN_SPEED;
		}
		else
		{
			if (_megaman.isLeft && _megaman.status == DASH)
			{
				_megaman.frameIndex = 0;
				_megaman.status = RUN;
				_megaman.dashTimer = 0;
				_megaman.speedX = RUN_SPEED;
			}
			else if (_megaman.status == DASHJUMPUP)
			{
				_megaman.status = DASHMOVEJUMPUP;
			}
			else if (_megaman.status == DASHJUMPDOWN)
			{
				_megaman.status = DASHMOVEJUMPDOWN;
			}

			if (_megaman.status == DASHMOVEJUMPUP || _megaman.status == DASHMOVEJUMPDOWN)
			{
				_megaman.speedX = DASH_SPEED;
			}
		}
		_megaman.isLeft = false;
	}
	else if (!_megaman.isLeft && (_megaman.status == RUN || _megaman.status == CATCH))
	{
		_megaman.frameIndex = 0;
		_megaman.status = STAY;
		_megaman.speedX = 0.0f;
	}
	else if (!_megaman.isLeft
		&& (_megaman.status == MOVEJUMPUP
		|| _megaman.status == MOVEJUMPDOWN
		|| _megaman.status == DASHMOVEJUMPUP
		|| _megaman.status == DASHMOVEJUMPDOWN))
	{
		_megaman.speedX = 0.0f;
		if (_megaman.status == MOVEJUMPUP) _megaman.status = JUMPUP;
		else if (_megaman.status == MOVEJUMPDOWN) _megaman.status = JUMPDOWN;
		else if (_megaman.status == DASHMOVEJUMPUP) _megaman.status = DASHJUMPUP;
		else if (_megaman.status == DASHMOVEJUMPDOWN) _megaman.status = DASHJUMPDOWN;
	}
	else if (!_megaman.isLeft && _megaman.status == MOVELINECATCH)
	{
		_megaman.speedX = 0.0f;
		_megaman.status = LINECATCH;
	}
	else if (!_megaman.isLeft && _megaman.status == MOVELINEUP)
	{
		_megaman.speedX = 0.0f;
		_megaman.status = LINEUPSTAY;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_megaman.status == STAY) _megaman.status = DOWNSTAY;
		else if (_megaman.status == LINEUPSTAY) _megaman.status = DOWNLINEUPSTAY;
		else if (_megaman.status == LINECATCH) _megaman.status = DOWNLINECATCH;
	}
	else if (_megaman.status == DOWNSTAY)
	{
		_megaman.status = STAY;
		_megaman.speedX = 0.0f;
	}
	else if (_megaman.status == DOWNLINEUPSTAY)
	{
		_megaman.status = LINEUPSTAY;
		_megaman.speedX = 0.0f;
	}
	else if (_megaman.status == DOWNLINECATCH)
	{
		_megaman.status = LINECATCH;
		_megaman.speedX = 0.0f;
	}

	if (KEYMANAGER->isOnceKeyDown('X') && _megaman.status != DASH)
	{
		if (_megaman.status == STAY || _megaman.status == RUN || _megaman.status == DOWNSTAY)
		{
			if(_megaman.isLeft) _megaman.frameIndex = _megamanImage[4]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = DASH;
			_megaman.dashTimer = 0;
		}
		_megaman.speedX = DASH_SPEED;
	}
	else if (KEYMANAGER->isOnceKeyUp('X') && _megaman.status == DASH)
	{
		_megaman.status = STAY;
		_megaman.speedX = 0.0f;
	}
	if (_megaman.status == DASH)
	{
		if (_megaman.dashTimer > MAX_DASH_TIME)
		{
			_megaman.status = STAY;
			_megaman.dashTimer = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown('C')
		&& _megaman.status != JUMPUP && _megaman.status != JUMPDOWN
		&& _megaman.status != DASHJUMPUP && _megaman.status != DASHJUMPDOWN
		&& _megaman.status != MOVEJUMPUP && _megaman.status != MOVEJUMPDOWN
		&& _megaman.status != DASHMOVEJUMPUP && _megaman.status != DASHMOVEJUMPDOWN)
	{
		_megaman.speedX = 0;
		if (_megaman.status == STAY
			|| _megaman.status == RUN
			|| _megaman.status == LINEUPSTAY
			|| _megaman.status == MOVELINEUP)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = JUMPUP;
			_megaman.speedY = JUMP_SPEED;
		}
		else if (_megaman.status == DOWNSTAY)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = DOWNJUMP;
		}
		else if (_megaman.status == DASH)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = DASHJUMPUP;
			_megaman.speedY = DASH_JUMP_SPEED;
		}
		else if (_megaman.status == CATCH)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.speedX = JUMP_SPEED * 1.5f;
			_megaman.speedY = JUMP_SPEED * 1.5f;
			_megaman.status = CATCHJUMP;
		}
		else if (_megaman.status == LINECATCH || _megaman.status == MOVELINECATCH)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.speedY = JUMP_SPEED;
			_megaman.status = JUMPUP;
		}
		else if (_megaman.status == DOWNLINECATCH)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = DOWNLINEJUMP;
		}
		else if (_megaman.status == DOWNLINEUPSTAY)
		{
			if (_megaman.isLeft) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
			else _megaman.frameIndex = 0;
			_megaman.status = DOWNLINEUPJUMP;
		}
	}

	megamanMove();
	megamanPixelCollision();
	_camera.viewPortSetting(_megaman.x, _megaman.y);
}
void megamanX6::render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	_mapImage->render(hdc, _camera.marginX, _camera.marginY, _camera.viewStartX, _camera.viewStartY, _camera.viewWidth, _camera.viewHeight);
	if(KEYMANAGER->isToggleKey(VK_F2)) IMAGEMANAGER->render("충돌 픽셀", getMemDC(), _camera.marginX, _camera.marginY, _camera.viewStartX, _camera.viewStartY, _camera.viewWidth, _camera.viewHeight);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _vObject.size(); i++)
		{
			if (!_vObject[i].isLine)
			{
				Rectangle(hdc, _vObject[i].point[0].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[0].y - _camera.viewStartY + _camera.marginY, _vObject[i].point[1].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[1].y - _camera.viewStartY + _camera.marginY);
			}
			else
			{
				LineMake(hdc, _vObject[i].point[0].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[0].y - _camera.viewStartY + _camera.marginY, _vObject[i].point[1].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[1].y - _camera.viewStartY + _camera.marginY);
				EllipseMakeCenter(hdc, _vObject[i].point[0].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[0].y - _camera.viewStartY + _camera.marginY, 5, 5);
				EllipseMakeCenter(hdc, _vObject[i].point[1].x - _camera.viewStartX + _camera.marginX, _vObject[i].point[1].y - _camera.viewStartY + _camera.marginY, 5, 5);
			}

		}
	}

	if (KEYMANAGER->isToggleKey(VK_F1)) Rectangle(hdc, _megaman.rc.left - _camera.viewStartX + _camera.marginX, _megaman.rc.top - _camera.viewStartY + _camera.marginY, _megaman.rc.right - _camera.viewStartX + _camera.marginX, _megaman.rc.bottom - _camera.viewStartY + _camera.marginY);
	megamanDrawImage(hdc);

	_minimapImage->render(hdc, WINSIZEX - _minimapImage->getWidth() - 100, 50);
	RECT megamanRc = RectMakeCenter(WINSIZEX - _minimapImage->getWidth() - 100 + _megaman.x / 10, 50 + _megaman.y / 10, 5, 8);
	HBRUSH brush = CreateSolidBrush(RGB(RND->getInt(256), 0, 0));
	if (0 <= _megaman.x && _megaman.x <= _camera.mapWidth
		&& 0 <= _megaman.y && _megaman.y <= _camera.mapHeight)
	{
		FillRect(hdc, &megamanRc, brush);
	}
	DeleteObject(brush);

	_bgImage->render(hdc);

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		char str[100];
		switch (_megaman.status)
		{
		case megamanX6::STAY:
			sprintf(str, "%s", "STAY");
			break;
		case megamanX6::DOWNSTAY:
			sprintf(str, "%s", "DOWNSTAY");
			break;
		case megamanX6::DOWNJUMP:
			sprintf(str, "%s", "DOWNJUMP");
			break;
		case megamanX6::RUN:
			sprintf(str, "%s", "RUN");
			break;
		case megamanX6::JUMPUP:
			sprintf(str, "%s", "JUMPUP");
			break;
		case megamanX6::JUMPDOWN:
			sprintf(str, "%s", "JUMPDOWN");
			break;
		case megamanX6::MOVEJUMPUP:
			sprintf(str, "%s", "MOVEJUMPUP");
			break;
		case megamanX6::MOVEJUMPDOWN:
			sprintf(str, "%s", "MOVEJUMPDOWN");
			break;
		case megamanX6::DASH:
			sprintf(str, "%s", "DASH");
			break;
		case megamanX6::DASHJUMPUP:
			sprintf(str, "%s", "DASHJUMPUP");
			break;
		case megamanX6::DASHJUMPDOWN:
			sprintf(str, "%s", "DASHJUMPDOWN");
			break;
		case megamanX6::DASHMOVEJUMPUP:
			sprintf(str, "%s", "DASHMOVEJUMPUP");
			break;
		case megamanX6::DASHMOVEJUMPDOWN:
			sprintf(str, "%s", "DASHMOVEJUMPDOWN");
			break;
		case megamanX6::CATCH:
			sprintf(str, "%s", "CATCH");
			break;
		case megamanX6::LINECATCH:
			sprintf(str, "%s", "LINECATCH");
			break;
		case megamanX6::DOWNLINECATCH:
			sprintf(str, "%s", "DOWNLINECATCH");
			break;
		case megamanX6::DOWNLINEJUMP:
			sprintf(str, "%s", "DOWNLINEJUMP");
			break;
		case megamanX6::MOVELINECATCH:
			sprintf(str, "%s", "MOVELINECATCH");
			break;
		case megamanX6::LINEUPSTAY:
			sprintf(str, "%s", "LINEUPSTAY");
			break;
		case megamanX6::MOVELINEUP:
			sprintf(str, "%s", "MOVELINEUP");
			break;
		case megamanX6::DOWNLINEUPJUMP:
			sprintf(str, "%s", "DOWNLINEUPJUMP");
			break;
		case megamanX6::DOWNLINEUPSTAY:
			sprintf(str, "%s", "DOWNLINEUPSTAY");
			break;
		default:
			break;
		}
		TextOut(hdc, 10, 10, str, strlen(str));

		char loc[200];
		sprintf(loc, "loc <%f, %f> speed <%f, %f>", _megaman.x, _megaman.y, _megaman.speedX, _megaman.speedY);
		TextOut(hdc, 10, 25, loc, strlen(loc));

		char rect[200];
		sprintf(rect, "rect <%d, %d, %d, %d> _count %d", _megaman.rc.left, _megaman.rc.top, _megaman.rc.right, _megaman.rc.bottom, _count);
		TextOut(hdc, 10, 40, rect, strlen(rect));
	}
}

void megamanX6::megamanMove()
{
	if (_megaman.rc.top <= _camera.mapHeight)
	{
		if (_megaman.status != DASH
			&& _megaman.status != LINECATCH
			&& _megaman.status != MOVELINECATCH)
		{
			if (_megaman.status != CATCH)
			{
				_megaman.y -= _megaman.speedY;
				_megaman.speedY -= GRAVITY;
			}
			else
			{
				_megaman.y += 1.0f;
			}
		}

		switch (_megaman.status)
		{
		case megamanX6::STAY:
		case megamanX6::DOWNSTAY:
		case megamanX6::DOWNJUMP:
			break;
		case megamanX6::RUN:
			if(_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			break;
		case megamanX6::JUMPUP:
			if (_megaman.speedY <= 0) _megaman.status = JUMPDOWN;
			break;
		case megamanX6::JUMPDOWN:
			break;
		case megamanX6::MOVEJUMPUP:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			if (_megaman.speedY <= 0) _megaman.status = MOVEJUMPDOWN;
			break;
		case megamanX6::MOVEJUMPDOWN:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			break;
		case megamanX6::DASH:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			_megaman.dashTimer++;
			if (_megaman.dashTimer > MAX_DASH_TIME)
			{
				_megaman.speedX = 0;
				_megaman.status = STAY;
			}
			break;
		case megamanX6::DASHJUMPUP:
			if (_megaman.speedY <= 0) _megaman.status = DASHJUMPDOWN;
			break;
		case megamanX6::DASHJUMPDOWN:
			break;
		case megamanX6::DASHMOVEJUMPUP:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			if (_megaman.speedY <= 0) _megaman.status = DASHMOVEJUMPDOWN;
			break;
		case megamanX6::DASHMOVEJUMPDOWN:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			break;
		case megamanX6::CATCHJUMP:
			if (_megaman.isLeft)
			{
				_megaman.x += _megaman.speedX;
				_megaman.y -= _megaman.speedY;
				_megaman.isLeft = true;
			}
			else
			{
				_megaman.x -= _megaman.speedX;
				_megaman.y -= _megaman.speedY;
				_megaman.isLeft = false;
			}
			_megaman.status = MOVEJUMPUP;
			_megaman.speedX = JUMP_SPEED;
			_megaman.speedY = JUMP_SPEED;
			break;
		case megamanX6::MOVELINECATCH:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			break;
		case megamanX6::MOVELINEUP:
			if (_megaman.isLeft) _megaman.x -= _megaman.speedX;
			else _megaman.x += _megaman.speedX;
			break;
		default:
			break;
		}
		_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);

	}
}

void megamanX6::megamanCollision()
{
	bool collision = false;
	RECT collisionBox = { 0, 0, 0, 0 };
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (!_vObject[i].isLine)
		{
			RECT objectRc = { _vObject[i].point[0].x, _vObject[i].point[0].y, _vObject[i].point[1].x, _vObject[i].point[1].y };
			if (IntersectRect(&collisionBox, &_megaman.rc, &objectRc))
			{
				if (objectRc.left <= _megaman.x && _megaman.x <= objectRc.right
					&& objectRc.top >= _megaman.y)
				{
					//위
					if (!_vObject[i].isOverlap && _vObject[i].isUpper && _megaman.status == DOWNJUMP)
					{
						_megaman.y = objectRc.top - _megaman.height / 2 + 1;
						_megaman.speedY = JUMP_SPEED;
						_megaman.status = JUMPUP;
						collision = true;
						continue;
					}

					if (_vObject[i].isUpper)
					{
						if (_megaman.status == DOWNJUMP)
						{
							_megaman.y = objectRc.top + 1;
							_megaman.status = JUMPDOWN;
						}
						else
						{
							if (_megaman.status == JUMPUP
								|| _megaman.status == MOVEJUMPUP
								|| _megaman.status == DASHJUMPUP
								|| _megaman.status == DASHMOVEJUMPUP) continue;

							_megaman.y = objectRc.top - _megaman.height / 2 + 1;
							_megaman.speedY = 0;
							if (_megaman.status == JUMPDOWN || _megaman.status == DASHJUMPDOWN
								|| _megaman.status == MOVEJUMPDOWN || _megaman.status == DASHMOVEJUMPDOWN
								|| _megaman.status == CATCH) _megaman.status = STAY;
						}
						collision = true;
					}
				}
				else if (objectRc.top <= _megaman.y && _megaman.y <= objectRc.bottom
					&& objectRc.left >= _megaman.x)
				{
					//왼쪽
					if (_megaman.status == STAY
						|| _megaman.status == DOWNSTAY) continue;

					if (!_vObject[i].isOverlap)
					{
						_megaman.x = objectRc.left - _megaman.width / 2 + 1;
						_megaman.speedX = 0;
						collision = true;
					}

					if (_vObject[i].isSideCatch)
					{
						if (!_megaman.isLeft
							&& (_megaman.status == MOVEJUMPUP || _megaman.status == MOVEJUMPDOWN
							|| _megaman.status == DASHMOVEJUMPUP || _megaman.status == DASHMOVEJUMPDOWN))
						{
							_megaman.x = objectRc.left - _megaman.width / 2 + 1;
							_megaman.speedX = 0;

							_megaman.frameIndex = 0;
							_megaman.status = CATCH;
							_megaman.speedX = 0;
							_megaman.speedY = 0;
							collision = true;
						}
						else if (!_megaman.isLeft && _megaman.status == CATCH)
						{
							_megaman.x = objectRc.left - _megaman.width / 2 + 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
				}
				else if (objectRc.top <= _megaman.y && _megaman.y <= objectRc.bottom
					&& objectRc.right <= _megaman.x)
				{
					//오른쪽
					if (_megaman.status == STAY || _megaman.status == STAY
						|| _megaman.status == DOWNSTAY || _megaman.status == DOWNSTAY) continue;

					if (!_vObject[i].isOverlap)
					{
						_megaman.x = objectRc.right + _megaman.width / 2 - 1;
						_megaman.speedX = 0;
						collision = true;
					}

					if (_vObject[i].isSideCatch)
					{
						if (_megaman.isLeft
							&& (_megaman.status == MOVEJUMPUP || _megaman.status == MOVEJUMPDOWN
							|| _megaman.status == DASHMOVEJUMPUP || _megaman.status == DASHMOVEJUMPDOWN))
						{
							_megaman.x = objectRc.right + _megaman.width / 2 - 1;
							_megaman.speedX = 0;

							_megaman.frameIndex = _megamanImage[3]->getMaxFrameX();
							_megaman.status = CATCH;
							_megaman.speedX = 0;
							_megaman.speedY = 0;

							collision = true;
						}
						else if (_megaman.isLeft && _megaman.status == CATCH)
						{
							_megaman.x = objectRc.right + _megaman.width / 2 - 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
				}
				else if (objectRc.left <= _megaman.x && _megaman.x <= objectRc.right
					&& objectRc.bottom <= _megaman.y)
				{
					//아래
					if (!_vObject[i].isOverlap)
					{
						_megaman.y = objectRc.bottom + _megaman.height / 2;
						_megaman.speedY = 0;
						if (_megaman.status == JUMPUP) _megaman.status = JUMPDOWN;
						else if (_megaman.status == DASHJUMPUP) _megaman.status = DASHJUMPDOWN;

						collision = true;
					}
				}
				else if (_megaman.x <= objectRc.left && _megaman.y <= objectRc.top)
				{
					//왼쪽위
					float inc1 = (_megaman.y - objectRc.top) / (_megaman.x - objectRc.left);
					float inc2 = (_megaman.y - _megaman.rc.top) / (_megaman.x - _megaman.rc.left);
					if (inc1 > inc2)
					{
						if (_megaman.status == JUMPUP
							|| _megaman.status == MOVEJUMPUP
							|| _megaman.status == DASH
							|| _megaman.status == DASHJUMPUP
							|| _megaman.status == DASHMOVEJUMPUP) continue;
						/* 버그해결을 위해 주석처리 해결방안 모색

						if (!_vObject[i].isOverlap && _vObject[i].isUpper && (_megaman.status == LEFTDOWNJUMP || _megaman.status == RIGHTDOWNJUMP))
						{
							_megaman.y = objectRc.top - _megaman.height / 2 + 1;
							_megaman.speedY = JUMP_SPEED;
							if (_megaman.status == LEFTDOWNJUMP) _megaman.status = LEFTJUMPUP;
							else if (_megaman.status == RIGHTDOWNJUMP) _megaman.status = RIGHTJUMPUP;
							continue;
						}

						if (_vObject[i].isUpper)
						{
							if (_megaman.status == LEFTDOWNJUMP)
							{
								_megaman.y = objectRc.top + 1;
								_megaman.status = LEFTJUMPDOWN;
							}
							else if (_megaman.status == RIGHTDOWNJUMP)
							{
								_megaman.y = objectRc.top + 1;
								_megaman.status = RIGHTJUMPDOWN;
							}
							else
							{
								_megaman.y = objectRc.top - _megaman.height / 2 + 1;
								_megaman.speedY = 0;
								if (_megaman.status == LEFTJUMPDOWN || _megaman.status == LEFTDASHJUMPDOWN
									|| _megaman.status == LEFTMOVEJUMPDOWN || _megaman.status == LEFTDASHMOVEJUMPDOWN) _megaman.status = LEFTSTAY;
								else if (_megaman.status == RIGHTJUMPDOWN || _megaman.status == RIGHTDASHJUMPDOWN
									|| _megaman.status == RIGHTMOVEJUMPDOWN || _megaman.status == RIGHTDASHMOVEJUMPDOWN) _megaman.status = RIGHTSTAY;
								else if (_megaman.status == LEFTCATCH) _megaman.status = LEFTSTAY;
								else if (_megaman.status == RIGHTCATCH) _megaman.status = RIGHTSTAY;
							}
						}
						*/

						if (!_vObject[i].isOverlap)
						{
							_megaman.x = objectRc.left - _megaman.width / 2 + 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
					else
					{
						if (_megaman.status == JUMPUP
							|| _megaman.status == MOVEJUMPUP
							|| _megaman.status == DASH
							|| _megaman.status == DASHJUMPUP
							|| _megaman.status == DASHMOVEJUMPUP) continue;

						if (!_vObject[i].isOverlap)
						{
							_megaman.x = objectRc.left - _megaman.width / 2 + 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
				}
				else if (_megaman.x >= objectRc.right && _megaman.y <= objectRc.top)
				{
					//오른쪽 위
					float inc1 = (_megaman.y - objectRc.top) / (_megaman.x - objectRc.right);
					float inc2 = (_megaman.y - _megaman.rc.left) / (_megaman.x - _megaman.rc.right);
					if (inc1 < inc2)
					{
						if (_megaman.status == JUMPUP
							|| _megaman.status == MOVEJUMPUP
							|| _megaman.status == DASH
							|| _megaman.status == DASHJUMPUP
							|| _megaman.status == DASHMOVEJUMPUP) continue;
						/* 버그해결을 위해 주석처리 해결방안 모색

						if (!_vObject[i].isOverlap && _vObject[i].isUpper && (_megaman.status == LEFTDOWNJUMP || _megaman.status == RIGHTDOWNJUMP))
						{
							_megaman.y = objectRc.top - _megaman.height / 2 + 1;
							_megaman.speedY = JUMP_SPEED;
							if (_megaman.status == LEFTDOWNJUMP) _megaman.status = LEFTJUMPUP;
							else if (_megaman.status == RIGHTDOWNJUMP) _megaman.status = RIGHTJUMPUP;
							continue;
						}

						if (_vObject[i].isUpper)
						{
							if (_megaman.status == LEFTDOWNJUMP)
							{
								_megaman.y = objectRc.top + 1;
								_megaman.status = LEFTJUMPDOWN;
							}
							else if (_megaman.status == RIGHTDOWNJUMP)
							{
								_megaman.y = objectRc.top + 1;
								_megaman.status = RIGHTJUMPDOWN;
							}
							else
							{
								_megaman.y = objectRc.top - _megaman.height / 2 + 1;
								_megaman.speedY = 0;
								if (_megaman.status == LEFTJUMPDOWN || _megaman.status == LEFTDASHJUMPDOWN
									|| _megaman.status == LEFTMOVEJUMPDOWN || _megaman.status == LEFTDASHMOVEJUMPDOWN) _megaman.status = LEFTSTAY;
								else if (_megaman.status == RIGHTJUMPDOWN || _megaman.status == RIGHTDASHJUMPDOWN
									|| _megaman.status == RIGHTMOVEJUMPDOWN || _megaman.status == RIGHTDASHMOVEJUMPDOWN) _megaman.status = RIGHTSTAY;
								else if (_megaman.status == LEFTCATCH) _megaman.status = LEFTSTAY;
								else if (_megaman.status == RIGHTCATCH) _megaman.status = RIGHTSTAY;
							}
						}
						*/

						if (!_vObject[i].isOverlap)
						{
							_megaman.x = objectRc.right + _megaman.width / 2 - 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
					else
					{
						if (_megaman.status == JUMPUP
							|| _megaman.status == MOVEJUMPUP
							|| _megaman.status == DASH
							|| _megaman.status == DASHJUMPUP
							|| _megaman.status == DASHMOVEJUMPUP) continue;

						if (!_vObject[i].isOverlap)
						{
							_megaman.x = objectRc.right + _megaman.width / 2 - 1;
							_megaman.speedX = 0;
							collision = true;
						}
					}
				}
				else if (_megaman.x < objectRc.left && _megaman.y > objectRc.bottom)
				{
					//왼쪽아래
					if (!_vObject[i].isOverlap)
					{
						float inc1 = (_megaman.y - objectRc.bottom) / (_megaman.x - objectRc.left);
						float inc2 = (_megaman.y - _megaman.rc.bottom) / (_megaman.x - _megaman.rc.left);
						if (inc1 <= inc2)
						{
							//임시로 주석처리 버그 해결을 위한
							//_megaman.y = objectRc.bottom + _megaman.height / 2;
							//_megaman.speedY = 0;

							_megaman.x = objectRc.left - _megaman.width / 2 - 1;
							_megaman.speedX = 0;
						}
						else
						{
							_megaman.x = objectRc.left - _megaman.width / 2 - 1;
							_megaman.speedX = 0;
						}
						collision = true;
					}
				}
				else if (_megaman.x > objectRc.right && _megaman.y > objectRc.bottom)
				{
					//오른쪽아래
					if (!_vObject[i].isOverlap)
					{
						float inc1 = (_megaman.y - objectRc.bottom) / (_megaman.x - objectRc.right);
						float inc2 = (_megaman.y - _megaman.rc.bottom) / (_megaman.x - _megaman.rc.right);
						if (inc1 >= inc2)
						{
							//임시로 주석처리 버그 해결을 위한
							//_megaman.y = objectRc.bottom + _megaman.height / 2;
							//_megaman.speedY = 0;
							_megaman.x = objectRc.right + _megaman.width / 2 + 1;
							_megaman.speedX = 0;
						}
						else
						{
							_megaman.x = objectRc.right + _megaman.width / 2 + 1;
							_megaman.speedX = 0;
						}
						collision = true;
					}
				}
			}
		}
		else
		{
			//선일경우
			if (intersectLineRect(&_vObject[i].point[0], &_vObject[i].point[1], &_megaman.rc))
			{
				float inc = (float)(_vObject[i].point[1].y - _vObject[i].point[0].y) / (float)(_vObject[i].point[1].x - _vObject[i].point[0].x);
				float y = inc * (_megaman.x - _vObject[i].point[0].x) + _vObject[i].point[0].y;
				if (_vObject[i].point[0].x <= _megaman.x && _megaman.x <= _vObject[i].point[1].x)
				{
					if (_megaman.y >= y)
					{
						if (_vObject[i].isLineCatch)
						{
							if (_megaman.status == JUMPDOWN || _megaman.status == DASHJUMPDOWN
								|| _megaman.status == MOVEJUMPDOWN || _megaman.status == DASHMOVEJUMPDOWN)
							{
								_megaman.y = y + _megaman.height / 2 - 10;
								_megaman.frameIndex = 0;
								_megaman.status = LINECATCH;
								_megaman.speedX = 0;
								_megaman.speedY = 0;

							}
							else if (_megaman.status == LINECATCH
								|| _megaman.status == MOVELINECATCH
								|| _megaman.status == DOWNLINECATCH)
							{
								_megaman.y = y + _megaman.height / 2 - 10;
								_megaman.speedY = 0;
							}
							else if (_megaman.status == DOWNLINEJUMP)
							{
								_megaman.y = y + _megaman.height;
								_megaman.status = JUMPDOWN;
							}
						}
					}
					else
					{
						if (_vObject[i].isUpper)
						{
							if (_megaman.status == JUMPDOWN || _megaman.status == DASHJUMPDOWN
								|| _megaman.status == MOVEJUMPDOWN || _megaman.status == DASHMOVEJUMPDOWN)
							{
								_megaman.y = y - _megaman.height / 2 + 1;
								_megaman.status = LINEUPSTAY;
								_megaman.speedX = 0;
								_megaman.speedY = 0;
							}
							else if (_megaman.status == LINEUPSTAY || _megaman.status == LINEUPSTAY
								|| _megaman.status == MOVELINEUP || _megaman.status == MOVELINEUP
								|| _megaman.status == DOWNLINEUPSTAY || _megaman.status == DOWNLINEUPSTAY)
							{
								_megaman.y = y - _megaman.height / 2 + 1;
								_megaman.speedY = 0;
							}
							else if (_megaman.status == DOWNLINEUPJUMP)
							{
								_megaman.y = y + 1;
								_megaman.status = JUMPDOWN;
							}
						}
					}
					collision = true;
				}
			}
		}
	}

	if (!collision && (_megaman.status == STAY || _megaman.status == RUN || _megaman.status == CATCH
		|| _megaman.status == LINECATCH || _megaman.status == MOVELINECATCH
		|| _megaman.status == LINEUPSTAY  || _megaman.status == MOVELINEUP))
	{
		if(_megaman.isLeft) _megaman.frameIndex = 3;
		else _megaman.frameIndex = 4;
		_megaman.status = JUMPDOWN;
	}
	_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
}

void megamanX6::megamanPixelCollision()
{
	bool collision = false;

	//천장과 충돌
	for (int j = _megaman.rc.top + 10; j >= _megaman.rc.top; j--)
	{
		COLORREF rgbLeft = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.left, j);
		COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.x, j);
		COLORREF rgbRight = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.right, j);

		if (_megaman.status == JUMPUP
			|| _megaman.status == MOVEJUMPUP
			|| _megaman.status == DASHJUMPUP
			|| _megaman.status == DASHMOVEJUMPUP)
		{
			if (_pixelMap["잡기o/통과x"] == rgbLeft
				|| _pixelMap["잡기o/통과x"] == rgbMiddle
				|| _pixelMap["잡기o/통과x"] == rgbRight)
			{
				_megaman.y = j + _megaman.height / 2 + 1;
				_megaman.speedY = 0;
				if (_megaman.status == JUMPUP) _megaman.status = JUMPDOWN;
				else if (_megaman.status == MOVEJUMPUP) _megaman.status = MOVEJUMPDOWN;
				else if (_megaman.status == DASHJUMPUP) _megaman.status = DASHJUMPDOWN;
				else if (_megaman.status == DASHMOVEJUMPUP) _megaman.status = DASHMOVEJUMPDOWN;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}
		}
	}

	//천장과 충돌
	for (int j = _megaman.rc.top; j < _megaman.rc.top + 20; j++)
	{
		COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.x, j);
		
		if (_pixelMap["줄(잡기&위에서기)"] == rgbMiddle)
		{
			if (_megaman.status == JUMPDOWN
				|| _megaman.status == DASHJUMPDOWN
				|| _megaman.status == LINECATCH)
			{
				_megaman.status = LINECATCH;
				_megaman.y = j + 15;
				_megaman.speedY = 0;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}
			else if (_megaman.status == DOWNLINECATCH)
			{
				_megaman.y = j + 15;
				_megaman.speedY = 0;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}
			else if (_megaman.status == MOVEJUMPDOWN
				|| _megaman.status == DASHMOVEJUMPDOWN
				|| _megaman.status == MOVELINECATCH)
			{
				_megaman.status = MOVELINECATCH;
				_megaman.y = j + 15;
				_megaman.speedY = 0;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}
			else if (_megaman.status == DOWNLINEJUMP)
			{
				_megaman.y = j + _megaman.height / 2 + 10;
				_megaman.speedY = 0;
				_megaman.status = JUMPDOWN;
				if (_megaman.isLeft) _megaman.frameIndex = 2;
				else _megaman.frameIndex = 5;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}
		}
	}

	//양옆과의 충돌
	if (_megaman.isLeft)
	{
		float x = _megaman.rc.left;
		for (int i = x + 10; i >= x; i--)
		{
			COLORREF rgbTop = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.rc.top);
			COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.y);
			COLORREF rgbBottom = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.rc.bottom);

			if (_megaman.status == MOVEJUMPUP
				|| _megaman.status == MOVEJUMPDOWN
				|| _megaman.status == DASHMOVEJUMPUP
				|| _megaman.status == DASHMOVEJUMPDOWN
				|| _megaman.status == CATCH)
			{
				if (_pixelMap["잡기o/통과x"] == rgbTop
					|| _pixelMap["잡기o/통과x"] == rgbMiddle
					|| _pixelMap["잡기o/통과x"] == rgbBottom
					|| _pixelMap["오른쪽에서잡기가능"] == rgbTop
					|| _pixelMap["오른쪽에서잡기가능"] == rgbMiddle
					|| _pixelMap["오른쪽에서잡기가능"] == rgbBottom)
				{
					_megaman.x = i + _megaman.width / 2 - 1;
					_megaman.status = CATCH;
					_megaman.speedX = 0;
					_megaman.speedY = 0;
					collision = true;
					break;
				}
			}
			else if (_megaman.status != JUMPDOWN && _megaman.status != DASHJUMPDOWN)
			{
				//통과 안됨
				if (_pixelMap["잡기o/통과x"] == rgbTop
					|| _pixelMap["잡기o/통과x"] == rgbMiddle
					|| _pixelMap["잡기o/통과x"] == rgbBottom)
				{
					_megaman.x = i + _megaman.width / 2 + 1;
					collision = true;
					break;
				}
			}

		}
	}
	else
	{
		float x = _megaman.rc.right;
		for (int i = x - 10; i <= x; i++)
		{
			COLORREF rgbTop = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.rc.top);
			COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.y);
			COLORREF rgbBottom = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), i, _megaman.rc.bottom);

			if (_megaman.status == MOVEJUMPUP
				|| _megaman.status == MOVEJUMPDOWN
				|| _megaman.status == DASHMOVEJUMPUP
				|| _megaman.status == DASHMOVEJUMPDOWN
				|| _megaman.status == CATCH)
			{
				if (_pixelMap["잡기o/통과x"] == rgbTop
					|| _pixelMap["잡기o/통과x"] == rgbMiddle
					|| _pixelMap["잡기o/통과x"] == rgbBottom
					|| _pixelMap["왼쪽에서잡기가능"] == rgbTop
					|| _pixelMap["왼쪽에서잡기가능"] == rgbMiddle
					|| _pixelMap["왼쪽에서잡기가능"] == rgbBottom)
				{
					_megaman.x = i - _megaman.width / 2 + 1;
					_megaman.status = CATCH;
					_megaman.frameIndex = 0;
					_megaman.speedX = 0;
					_megaman.speedY = 0;
					collision = true;
					break;
				}
			}
			else if (_megaman.status != JUMPDOWN && _megaman.status != DASHJUMPDOWN)
			{
				if (_pixelMap["잡기o/통과x"] == rgbTop
					|| _pixelMap["잡기o/통과x"] == rgbMiddle
					|| _pixelMap["잡기o/통과x"] == rgbBottom)
				{
					_megaman.x = i - _megaman.width / 2 - 1;
					collision = true;
					break;
				}
			}

		}
	}
	_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);

	//바닥과의 충돌
	for (int j = _megaman.rc.bottom - 10; j < _megaman.rc.bottom + 5; j++)
	{
		COLORREF rgbLeft = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.left, j);
		COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.x, j);
		COLORREF rgbRight = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.right, j);

		if (_megaman.status == CATCH)
		{
			if (_megaman.isLeft) rgbLeft = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.left + 2, j);
			else rgbRight = GetPixel(IMAGEMANAGER->findImage("충돌 픽셀")->getMemDC(), _megaman.rc.right - 2, j);
		}

		//아래키 누른상태에서 점프키
		if (_megaman.status == DOWNJUMP)
		{
			if (_pixelMap["잡기o/통과x"] == rgbLeft
				|| _pixelMap["잡기o/통과x"] == rgbMiddle
				|| _pixelMap["잡기o/통과x"] == rgbRight)
			{
				_megaman.y = j - _megaman.height / 2 - 1;
				_megaman.status = JUMPUP;
				_megaman.speedY = JUMP_SPEED;
				collision = true;
				break;
			}
			else if ((_pixelMap["통과되는벽1"] == rgbLeft
				|| _pixelMap["통과되는벽1"] == rgbMiddle
				|| _pixelMap["통과되는벽1"] == rgbRight)
				|| (_pixelMap["통과되는벽2"] == rgbLeft
				|| _pixelMap["통과되는벽2"] == rgbMiddle
				|| _pixelMap["통과되는벽2"] == rgbRight))
			{
				_megaman.y = j;
				_megaman.status = JUMPDOWN;
				if (_megaman.isLeft) _megaman.frameIndex = 2;
				else _megaman.frameIndex = 5;
				_megaman.speedY = 0;
				collision = true;
				break;
			}
		}
		else if (_megaman.status == DOWNLINEUPJUMP)
		{
			if (_pixelMap["줄(잡기&위에서기)"] == rgbLeft
				|| _pixelMap["줄(잡기&위에서기)"] == rgbMiddle
				|| _pixelMap["줄(잡기&위에서기)"] == rgbRight)
			{
				_megaman.y = j + 10;
				_megaman.status = JUMPDOWN;
				if(_megaman.isLeft) _megaman.frameIndex = 2;
				else _megaman.frameIndex = 5;
				collision = true;
				break;
			}
		}

		//위에서기
		if ((_pixelMap["잡기o/통과x"] == rgbLeft
			|| _pixelMap["잡기o/통과x"] == rgbMiddle
			|| _pixelMap["잡기o/통과x"] == rgbRight)
			|| (_pixelMap["통과되는벽1"] == rgbLeft
			|| _pixelMap["통과되는벽1"] == rgbMiddle
			|| _pixelMap["통과되는벽1"] == rgbRight)
			|| (_pixelMap["통과되는벽2"] == rgbLeft
			|| _pixelMap["통과되는벽2"] == rgbMiddle
			|| _pixelMap["통과되는벽2"] == rgbRight))
		{
			if (_megaman.status == JUMPUP
				|| _megaman.status == MOVEJUMPUP
				|| _megaman.status == DASHJUMPUP
				|| _megaman.status == DASHMOVEJUMPUP
				|| _megaman.status == DASH) continue;

			_megaman.y = j - _megaman.height / 2 - 1;
			_megaman.speedY = 0;
			if (_megaman.status == MOVEJUMPDOWN
				|| _megaman.status == RUN
				|| _megaman.status == DASHMOVEJUMPDOWN) _megaman.status = RUN;
			else if (_megaman.status == DOWNSTAY) _megaman.status = DOWNSTAY;
			else  _megaman.status = STAY;
			_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
			collision = true;
			break;
		}

		if (_pixelMap["줄(잡기&위에서기)"] == rgbLeft
			|| _pixelMap["줄(잡기&위에서기)"] == rgbMiddle
			|| _pixelMap["줄(잡기&위에서기)"] == rgbRight)
		{
			if (_megaman.status == JUMPUP
				|| _megaman.status == MOVEJUMPUP
				|| _megaman.status == DASHJUMPUP
				|| _megaman.status == DASHMOVEJUMPUP) continue;

			if (_megaman.status == DASH)
			{
				_megaman.y = j - _megaman.height / 2 - 1;
				_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
				collision = true;
				break;
			}

			_megaman.y = j - _megaman.height / 2 - 1;
			_megaman.speedY = 0;
			if (_megaman.status == MOVEJUMPDOWN
				|| _megaman.status == RUN
				|| _megaman.status == DASHMOVEJUMPDOWN
				|| _megaman.status == MOVELINEUP) _megaman.status = MOVELINEUP;
			else if (_megaman.status == DOWNSTAY || _megaman.status == DOWNLINEUPSTAY) _megaman.status = DOWNLINEUPSTAY;
			else  _megaman.status = LINEUPSTAY;
			_megaman.rc = RectMakeCenter(_megaman.x, _megaman.y, _megaman.width, _megaman.height);
			collision = true;
			break;
		}
	}

	if (!collision && (_megaman.status == STAY || _megaman.status == RUN || _megaman.status == CATCH
		|| _megaman.status == LINECATCH || _megaman.status == MOVELINECATCH
		|| _megaman.status == LINEUPSTAY || _megaman.status == MOVELINEUP))
	{
		if (_megaman.isLeft) _megaman.frameIndex = 2;
		else _megaman.frameIndex = 5;
		_megaman.status = JUMPDOWN;
	}
}

void megamanX6::megamanDrawImage(HDC hdc)
{
	switch (_megaman.status)
	{
	case megamanX6::STAY:
	case megamanX6::LINEUPSTAY:
		_megamanImage[0]->frameRender(hdc, _megaman.x - _megaman.width / 2 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 + 2 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		if (_megaman.isLeft)
		{
			if (_count % 10 == 0)_megaman.frameIndex--;
			if (_megaman.frameIndex < 0) _megaman.frameIndex = _megamanImage[0]->getMaxFrameX();
		}
		else
		{
			if (_count % 10 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > _megamanImage[0]->getMaxFrameX()) _megaman.frameIndex = 0;
		}
		break;
	case megamanX6::DOWNSTAY:
	case megamanX6::DOWNJUMP:
	case megamanX6::DOWNLINEUPSTAY:
	case megamanX6::DOWNLINEUPJUMP:
		_megamanImage[6]->frameRender(hdc, _megaman.x - _megaman.width / 2 - 1 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 + 16 - _camera.viewStartY + _camera.marginY, 0, _megaman.isLeft);
		break;
		break;
	case megamanX6::RUN:
	case megamanX6::MOVELINEUP:
		_megamanImage[1]->frameRender(hdc, _megaman.x - _megaman.width / 2 - 5 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 1 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		if (_megaman.isLeft)
		{
			if (_count % 2 == 0) _megaman.frameIndex--;
			if (_megaman.frameIndex < 0) _megaman.frameIndex = _megamanImage[1]->getMaxFrameX();
		}
		else
		{
			if (_count % 2 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > _megamanImage[1]->getMaxFrameX()) _megaman.frameIndex = 0;
		}
		break;
	case megamanX6::JUMPUP:
	case megamanX6::MOVEJUMPUP:
	case megamanX6::DASHJUMPUP:
	case megamanX6::DASHMOVEJUMPUP:
	case megamanX6::CATCHJUMP:
		_megamanImage[2]->frameRender(hdc, _megaman.x - _megaman.width / 2 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 5 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		if (_megaman.isLeft)
		{
			if (_count % 5 == 0) _megaman.frameIndex--;
			if (_megaman.frameIndex < 3) _megaman.frameIndex = 3;
		}
		else
		{
			if (_count % 5 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > 4) _megaman.frameIndex = 4;
		}
		break;
	case megamanX6::JUMPDOWN:
	case megamanX6::MOVEJUMPDOWN:
	case megamanX6::DASHJUMPDOWN:
	case megamanX6::DASHMOVEJUMPDOWN:
		_megamanImage[2]->frameRender(hdc, _megaman.x - _megaman.width / 2 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 5 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		if (_megaman.isLeft)
		{
			if (_count % 5 == 0) _megaman.frameIndex--;
			if (_megaman.frameIndex < 0) _megaman.frameIndex = 0;
		}
		else
		{
			if (_count % 5 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > _megamanImage[2]->getMaxFrameX()) _megaman.frameIndex = _megamanImage[2]->getMaxFrameX();
		}
		break;
	case megamanX6::DASH:
		_megamanImage[4]->frameRender(hdc, _megaman.x - _megaman.width / 2 - 5 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		if (_megaman.isLeft)
		{
			if (_count % 3 == 0) _megaman.frameIndex--;
			if (_megaman.frameIndex < 0) _megaman.frameIndex = 0;
		}
		else
		{
			if (_count % 3 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > _megamanImage[4]->getMaxFrameX()) _megaman.frameIndex = _megamanImage[4]->getMaxFrameX();
		}
		break;
	case megamanX6::CATCH:
		if (_megaman.isLeft)
		{
			_megamanImage[3]->frameRender(hdc, _megaman.x - _megaman.width / 2 - 3 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 5 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
			if (_count % 5 == 0) _megaman.frameIndex--;
			if (_megaman.frameIndex < 0) _megaman.frameIndex = 0;
		}
		else
		{
			_megamanImage[3]->frameRender(hdc, _megaman.x - _megaman.width / 2 + 5 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 5 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
			if (_count % 5 == 0) _megaman.frameIndex++;
			if (_megaman.frameIndex > _megamanImage[3]->getMaxFrameX()) _megaman.frameIndex = _megamanImage[3]->getMaxFrameX();
		}
		break;
	case megamanX6::LINECATCH:
	case megamanX6::DOWNLINECATCH:
	case megamanX6::DOWNLINEJUMP:
	case megamanX6::MOVELINECATCH:
		_megamanImage[5]->frameRender(hdc, _megaman.x - _megaman.width / 2 + 3 - _camera.viewStartX + _camera.marginX, _megaman.y - _megaman.height / 2 - 3 - _camera.viewStartY + _camera.marginY, _megaman.frameIndex, _megaman.isLeft);
		break;
	default:
		break;
	}
	_count++;
	if (_count >= 100) _count = 0;
}

bool megamanX6::intersectLineRect(LPPOINT point1, LPPOINT point2, LPRECT rc)
{
	float inc = (float)(point2->y - point1->y) / (float)(point2->x - point1->x);
	//제일 왼쪽점
	float x1 = rc->left;
	float y1 = inc * (x1 - point1->x) + point1->y;
	//가운데
	float x2 = rc->left + (rc->right - rc->left) / 2;
	float y2 = inc * (x2 - point1->x) + point1->y;
	//마지막
	float x3 = rc->right;
	float y3 = inc * (x3 - point1->x) + point1->y;

	if ((rc->top <= y1 && y1 <= rc->bottom && point1->x <= x1 && x1 <= point2->x)
		|| (rc->top <= y2 && y2 <= rc->bottom && point1->x <= x2 && x2 <= point2->x)
		|| (rc->top <= y3 && y3 <= rc->bottom && point1->x <= x3 && x3 <= point2->x)) return true;
	return false;
}