#include "stdafx.h"
#include "mainGame.h"
//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	gameNode::init(TRUE);
	//�̰����� �ʱ�ȭ�� �Ѵ�

	/*�� �߰��ϱ�*/
	SCENEMANAGER->addScene("�׽�Ʈ", new sceneTest);
	SCENEMANAGER->addScene("���ð���", new shootingGame);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("����������", new snowBrothers);

	/*���� �� ����*/
	SCENEMANAGER->changeScene("����������");


	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();
}

//==================================================================
//		## ���� ## render(void)
//==================================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �״�� �Ѱ�!!!)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//==================================================================
	
	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ���� (������ �Կ��� �ּ����� �����ϱ�)
	TIMEMANAGER->render(getMemDC());

//==================================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �Ѱ�!!)
	this->getBackBuffer()->render(getHDC());
}