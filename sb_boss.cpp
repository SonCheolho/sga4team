#include "stdafx.h"
#include "sb_boss.h"



HRESULT sb_boss::init(void)
{
	_bossImage = IMAGEMANAGER->addFrameImage("��������", "image/�Ϲݺ���2.bmp", 2041, 200, 6, 1, true, RGB(255, 0, 255));
	
	_bossEffectImage = IMAGEMANAGER->addFrameImage("��������Ʈ", "fx/boss_fx_ground.bmp", 381, 410, 1, 5, true, RGB(255, 0, 255));



	_BossPoint.x = 672;
	_BossPoint.y = 800;
	_MoveY = 0;
	_bosseffect = RectMakeCenter(_BossPoint.x / 2, 680 + _MoveY, 381, 82);
	_bossRc = RectMakeCenter(_BossPoint.x / 2, _BossPoint.y + _MoveY, 340, 200);

	_EffectIndex = 0;
	_bossindex = 0;
	_count = 0;

	fire = false;
	start = false;


	return S_OK;
}

void sb_boss::release(void)
{
}

void sb_boss::update(void)
{
	if (_BossPoint.y > 600 && start==true && _count % 2==0)
	{
		_BossPoint.y--;
	}
	//������ �߻��Ҷ� �����ӷ��� ��Ű��
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		fire = true;
	}

	if (fire == true && _count % 30 == 0)
	{
		_bossindex++;
	}


	//��Ʈ �̵�
	_bossRc = RectMakeCenter(_BossPoint.x / 2, _BossPoint.y + _MoveY, 340, 200);
	_bosseffect = RectMakeCenter(_BossPoint.x / 2, 680 + _MoveY, 381, 82);

}

void sb_boss::render(void)
{
	_count++;
	if (_count % 20 == 0&& start == true)
	{
		_EffectIndex++;
		if (_count > 100) _count = 0;

	}
	
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		RectangleMake(getMemDC(), _bosseffect);
		RectangleMake(getMemDC(), _bossRc);
		start = true;
	}
	
	_bossImage->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _bossindex, 0);
	if (_bossindex == _bossImage->getMaxFrameX() + 1)
	{
		_bossindex = 0;
		fire = false;
	}

	_bossEffectImage->frameRender(getMemDC(), _bosseffect.left, _bosseffect.top, 0, _EffectIndex);
	if (_EffectIndex == _bossEffectImage->getMaxFrmaeY() + 1) _EffectIndex = 0;
}
