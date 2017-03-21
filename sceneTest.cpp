#include "stdafx.h"
#include "sceneTest.h"


HRESULT sceneTest::init(void)
{
	return S_OK;
}

void sceneTest::release(void)
{
}

void sceneTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("슈팅게임");
	}
}

void sceneTest::render(void)
{
	char str[128];
	TextOut(getMemDC(), 100, 100, "씬테스트중임~~~", strlen("씬테스트중임~~~"));
}

