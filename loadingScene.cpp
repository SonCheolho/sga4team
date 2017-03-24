#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	//�ε��� �Ϸ�Ǹ� ȭ����ȯ
	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("�׽�Ʈ");
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ ����� ����
	//for (int i = 0; i < 1000; i++)
	//{
	//	_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	//}
	//���������� �̹��� �ֱ�
	_loading->loadImage("stage1", "image/1_1.bmp", 672, 720);
	_loading->loadImage("stage2", "image/2_1.bmp", 672, 720);
	_loading->loadFrameImage("stage3", "image/3_1.bmp", 672, 720,2,1);
	_loading->loadImage("stage1-2", "image/1_2.bmp", 672, 720);
	_loading->loadImage("stage1-3", "image/1_3.bmp", 672, 720);
	_loading->loadImage("stage2-2", "image/2_2.bmp", 672, 720);
	_loading->loadImage("stage2-3", "image/2_3.bmp", 672, 720);
	_loading->loadImage("stage3-2", "image/3_2.bmp", 672, 720);
	_loading->loadImage("stage3-3", "image/3_3.bmp", 672, 720);

}


void loadingScene::loadingSound(void)
{
}
