#include "stdafx.h"
#include "sb_player.h"
#include "snowBrothers.h"


HRESULT sb_player::init(void)
{
	ZeroMemory(&_player, sizeof(_player));
	
	_player.img[IDLE] = IMAGEMANAGER->addFrameImage("IDLE", "image/캐릭터_IDLE.bmp", 102, 75, 2, 1, true, RGB(255, 0, 255));
	_player.img[WALK] = IMAGEMANAGER->addFrameImage("WALK", "image/캐릭터_WALK.bmp", 184, 154, 4, 2, true, RGB(255, 0, 255));
	_player.img[JUMP] = IMAGEMANAGER->addFrameImage("JUMP", "image/캐릭터_JUMP.bmp", 378, 164, 7, 2, true, RGB(255, 0, 255));
	
	_player.img[DROP] = IMAGEMANAGER->addFrameImage("DROP", "image/캐릭터_DROP.bmp", 108, 82, 2, 1, true, RGB(255, 0, 255));

	_player.isRight = true;
	_player.isJumpDown = false;
	_player.x = 100;
	
	//_player.y = _bgImage->getHeight() - 80;
	//_player.y = _snowBrothers->getTestImage()->getHeight() - 80;
	_player.y = IMAGEMANAGER->findImage("테스트배경")->getHeight() - 80;
	
	_player.width = _player.img[IDLE]->getFrameWidth();
	_player.height = _player.img[IDLE]->getFrameHeight();
	_player.state = IDLE;
	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

	return S_OK;
}

void sb_player::release(void)
{
}

void sb_player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (_player.state == IDLE || _player.state == WALK || _player.state == RUN || _player.state == JUMP || _player.state == DROP)
		{
			if (_player.state != JUMP)
			{
				
				_player.state = WALK;
			}
			_player.isRight = false;
			_player.speedX = WALK_SPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_player.state != ATTACK && _player.state != JUMP)
		{
			_player.index = 0;
			_player.state = IDLE;
			_player.speedX = 0.0f;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_player.state == IDLE || _player.state == WALK || _player.state == RUN || _player.state == JUMP || _player.state == DROP)
		{
			if (_player.state != JUMP)
			{
				
				_player.state = WALK;
			}
			_player.isRight = true;
			_player.speedX = WALK_SPEED;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_player.state != ATTACK && _player.state != JUMP)
		{
			_player.index = 0;
			_player.state = IDLE;
			_player.speedX = 0.0f;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_player.index = 0;
		_player.state = JUMP;
		_player.speedY = JUMP_SPEED;
		_player.isJumpDown = false;
	}


	_player.rc = RectMakeCenter(_player.x, _player.y, _player.width, _player.height);

	this->playerMove();
	this->pixelCollision();
}

void sb_player::render(void)
{
	this->playerFrame();

	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), _player.rc);
		char str[128];
		sprintf(str, "%d", _player.state);
		TextOut(getMemDC(), 100, 100, str, sizeof(str));
	}
}

void sb_player::playerMove(void)
{
	switch (_player.state)
	{
	case WALK:
		if (_player.isRight) _player.x += _player.speedX;
		else _player.x -= _player.speedX;
		break;
	case JUMP:
		if (_player.isRight) _player.x += _player.speedX;
		else _player.x -= _player.speedX;
		_player.y -= _player.speedY;
		_player.speedY -= GRAVITY;
		if (_player.speedY <= 0) _player.isJumpDown = true;
		break;
	case DROP:
		_player.y -= _player.speedY;
		_player.speedY -= GRAVITY;
		break;
	}
}

void sb_player::playerFrame(void)
{
	switch (_player.state)
	{
	case IDLE:
		_player.img[_player.state]->frameRender(getMemDC(), _player.x - _player.width / 2, _player.y - _player.height / 2, _player.isRight, 0);

		break;
	case WALK:
		_player.img[_player.state]->frameRender(getMemDC(), _player.x - _player.width / 2, _player.y - _player.height / 2, _player.index, _player.isRight);
		if (_count % 20 == 0) _player.index++;
		if (_player.index == _player.img[_player.state]->getMaxFrameX() + 1) _player.index = 0;

		break;
	case JUMP:
		_player.img[_player.state]->frameRender(getMemDC(), _player.x - _player.width / 2, _player.y - _player.height / 2, _player.index, _player.isRight);
		if (_count % 15 == 0) _player.index++;
		//if (_player.index == _player.img[_player.state]->getMaxFrameX() + 1) _player.index = 0;
		break;
	case DROP:
		_player.img[_player.state]->frameRender(getMemDC(), _player.x - _player.width / 2, _player.y - _player.height / 2, _player.isRight, 0);
		break;
	}
	_count++;
}

void sb_player::pixelCollision(void)
{
	
	switch (_player.state)
	{
	case IDLE:
		for (int i = _player.rc.bottom - 1; i < _player.rc.bottom + 1; i++)
		{
			COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _player.x, i);
			int r = GetRValue(rgbMiddle);
			int g = GetGValue(rgbMiddle);
			int b = GetBValue(rgbMiddle);
			if (!(r == 0 && g == 0 && b == 0))
			{
				_player.state = DROP;
			}
		}
		break;
	case JUMP:
		for (int i = _player.rc.bottom - 1; i < _player.rc.bottom + 1; i++)
		{
			if (_player.isJumpDown == true)
			{
				COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _player.x, i);
				COLORREF rgbTemp = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _player.x, i - 5);
				int r = GetRValue(rgbMiddle);
				int g = GetGValue(rgbMiddle);
				int b = GetBValue(rgbMiddle);
				int r1 = GetRValue(rgbTemp);
				int g1 = GetGValue(rgbTemp);
				int b1 = GetBValue(rgbTemp);
				if (r == 0 && g == 0 && b == 0 && r1 == 255 && g1 == 0 && b1 == 255)
				{
					_player.speedX = 0.0f;
					_player.speedY = 0.0f;
					_player.state = IDLE;
					_player.count = 0;
					_player.index = 0;
					_player.isJumpDown = false;
					_player.y = i - _player.height / 2 - 1;
					break;
				}
			}
		}
		break;
	case DROP:
		for (int i = _player.rc.bottom - 1; i < _player.rc.bottom + 1; i++)
		{
			COLORREF rgbMiddle = GetPixel(IMAGEMANAGER->findImage("충돌용배경")->getMemDC(), _player.x, i);
			int r = GetRValue(rgbMiddle);
			int g = GetGValue(rgbMiddle);
			int b = GetBValue(rgbMiddle);
			if (r == 0 && g == 0 && b == 0)
			{
				_player.speedX = 0.0f;
				_player.speedY = 0.0f;
				_player.state = IDLE;
				_player.count = 0;
				_player.index = 0;
				_player.y = i - _player.height / 2;
			}
		}
	}
	
}
