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
		SCENEMANAGER->changeScene("���ð���");
	}
}

void sceneTest::render(void)
{
	char str[128];
	TextOut(getMemDC(), 100, 100, "���׽�Ʈ����~~~", strlen("���׽�Ʈ����~~~"));
}

