#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//이곳에서 초기화를 한다

	/*씬 추가하기*/
	SCENEMANAGER->addScene("테스트", new sceneTest);
	SCENEMANAGER->addScene("슈팅게임", new shootingGame);
	SCENEMANAGER->addScene("로딩화면", new loadingScene);
	SCENEMANAGER->addScene("스노우브라더스", new snowBrothers);

	/*시작 씬 설정*/
	SCENEMANAGER->changeScene("스노우브라더스");


	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();

	//씬매니져 업데이트
	SCENEMANAGER->update();
}

//==================================================================
//		## 렌더 ## render(void)
//==================================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵 (이것도 렌더에 그냥 그대로 둘것!!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//==================================================================
	
	//씬매니져 렌더
	SCENEMANAGER->render();

	//타임매니져 렌더 (동영상 촬영시 주석으로 봉인하기)
	TIMEMANAGER->render(getMemDC());

//==================================================================
	//백버퍼의 내용을 HDC에 그린다 (이것도 렌더에 그냥 둘것!!)
	this->getBackBuffer()->render(getHDC());
}