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
		//����, Ű, ����� �� �߰��ϱ�
		INIDATA->addData("�ظ�", "����", "10");
		INIDATA->addData("����", "������", "70");
		INIDATA->addData("�¾�", "����", "4");
		INIDATA->addData("�¾�", "���ŷ�", "108");
		INIDATA->addData("öȣ", "���밨��", "99");
		INIDATA->addData("����", "����", "30");

		//�����̸����� ���̺�
		INIDATA->saveINI("����4��");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int test = INIDATA->loadDataInteger("����4��", "öȣ", "���밨��");
		cout << test << endl;
	}

}

void iniTestScene::render(void)
{
}
