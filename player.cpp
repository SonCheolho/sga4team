#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init(void)
{
	//로켓(플레이어) 이미지 초기화 및 위치세팅
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY - 100;
	_rc = RectMake(_x, _y, 52, 64);

	//미사일클래스 생성 및 초기화
	_missile = new missile;
	_missile->init(10, 500);
	_missileM1 = new missileM1;
	_missileM1->init(5, 600);

	//체력바 클래스 생성후 초기화
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _rocket->getX(), _rocket->getY() - 50, 50, 10);
	//피통 초기화
	_maxHp = 100;
	_currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void player::release(void)
{
	//미사일클래스 해제
	_missile->release();
	SAFE_DELETE(_missile);
	SAFE_DELETE(_missileM1);

	//체력바 클래스 해제
	SAFE_DELETE(_hpBar);
}

void player::update(void)
{
	//플레이어 움직이면서 화면밖으로 못나가게 처리
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		//이미지로 좌표 움직이기
		_rocket->setX(_rocket->getX() - 5);
		_x -= 5;
	}
	//플레이어 움직이면서 화면밖으로 못나가게 처리
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() + _rocket->getWidth() < WINSIZEX)
	{
		//이미지로 좌표 움직이기
		_rocket->setX(_rocket->getX() + 5);
		_x += 5;
	}
	//총알발사
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//퐈이야~~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_missileM1->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//미사일 클래스 업데이트
	_missile->update();
	_missileM1->update();

	//렉트도 좌표만큼 계속 업데이트 해준다
	_rc = RectMake(_x, _y, 52, 64);

	//충돌함수
	this->collision();

	//체력바 업데이트
	_hpBar->update();
	//체력바가 플레이어 머리위에 따라다니게 만들기
	_hpBar->setX(_rocket->getX());
	_hpBar->setY(_rocket->getY() - 15);
	_hpBar->setGauge(_currentHp, _maxHp);

	/*
	//세이브
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//atoi => 문자를 정수로
		//itoa => 정수를 문자로
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(_rocket->getX(), temp, 10));
		vStr.push_back(itoa(_rocket->getY(), temp, 10));
		vStr.push_back(itoa(_currentHp, temp, 10));

		TXTDATA->txtSave("save.txt", vStr);
	}
	//로드
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save.txt");
		_rocket->setX(atoi(vStr[0].c_str()));
		_rocket->setY(atoi(vStr[1].c_str()));
		_currentHp = atoi(vStr[2].c_str());
	}
	*/

}

void player::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		RectangleMake(getMemDC(), _rc);
	}
	//로켓이미지 렌더
	_rocket->render(getMemDC());

	//미사일 클래스 렌더
	_missile->render();
	_missileM1->render();

	//체력바 렌더
	_hpBar->render();
}

void player::removeMissileM1(int index)
{
	_missileM1->removeBullet(index);
}

void player::collision(void)
{
	for (int i = 0; i < _missileM1->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_missileM1->getVBullet()[i].rc, &_em->getVMinion()[j]->getRect()))
			{
				_missileM1->removeBullet(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}
