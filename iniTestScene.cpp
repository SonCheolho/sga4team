#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init(void)
{
	return S_OK;
}

void iniTestScene::release(void)
{
}

void iniTestScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//섹션, 키, 밸류로 값 추가하기
		INIDATA->addData("준모", "지각", "10");
		INIDATA->addData("성희", "과제율", "70");
		INIDATA->addData("태언", "아이", "4");
		INIDATA->addData("태언", "정신력", "108");
		INIDATA->addData("철호", "공대감성", "99");
		INIDATA->addData("영진", "나이", "30");

		//파일이름으로 세이브
		INIDATA->saveINI("개발4팀");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int test = INIDATA->loadDataInteger("개발4팀", "철호", "공대감성");
		cout << test << endl;
	}

}

void iniTestScene::render(void)
{
}
