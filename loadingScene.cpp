#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩이 완료되면 화면전환
	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("테스트");
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	for (int i = 0; i < 1000; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}
}

void loadingScene::loadingSound(void)
{
}
