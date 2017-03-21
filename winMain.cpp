//====================================================================
//			## ������� ���ش� ##
//====================================================================
#include "stdafx.h"
#include "mainGame.h"
//====================================================================
//			## �������� ���ش� ##
//====================================================================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

//���ΰ��� Ŭ���� �����Ҵ�
mainGame mg;

//====================================================================
//			## �Լ� ���漱�� ##
//====================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//====================================================================
//			## ������ �����Լ� ##
//====================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//�������� ����
	//1. ������ â ������ ȭ�鿡 ����
	//2. �޼��� ����

	//�ν��Ͻ��� ���������� ��Ƶд�
	_hInstance = hInstance;

	//WNDCLASS : ������â�� ������ �����ϱ� ���� ����ü
	//������Ŭ���� ����ü ������ �ʱ�ȭ
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ â ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WS_OVERLAPPEDWINDOW,	//������ ��Ÿ��
		WINSTARTX,				//������ ȭ�� x��ǥ
		WINSTARTY,				//������ ȭ�� y��ǥ
		WINSIZEX,				//������ ȭ�� ����ũ��
		WINSIZEY,				//������ ȭ�� ����ũ��
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ�
		NULL					//������ �� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� ������ NULL(�츰 �� NULL����ϸ� ��)
	);

	//������ Ŭ���̾�Ʈ���� ��Ȯ�� �����ϱ� 
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ֱ�
	ShowWindow(_hWnd, nCmdShow);

	//���ΰ��� Ŭ���� �ʱ�ȭ
	if (FAILED(mg.init()))
	{
		return 0;
	}

	//MSG : �ü������ �߻��ϴ� �޼��� ������ �����ϱ� ���� ����ü
	MSG message;
	//GetMessage : �޼����� ������ �� ���������� �����ִ� �Լ�
	//PeekMessage : �޼����� ������ ���ϵǴ� �Լ�

	while (true) //���ӿ�
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			mg.update();
			mg.render();
		}
	}

	/*
	//�޼�������
	while (GetMessage(&message, 0, 0, 0))
	{
		//TranslateMessage : Ű���� �Է¸޽��� ó���� ���
		//�Էµ� Ű�� ����Ű���� Ȯ���� �빮��, �ҹ���, �ѱ�, ����
		//WM_CHAR�޼����� �߻���Ų��
		//DispatchMessage : ������ ���ν������� ���޵� �޼�����
		//���� ������� �������ش�
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/

	//���ΰ��� Ŭ���� ����
	mg.release();

	//������ Ŭ���� �������
	UnregisterClass(WINNAME, hInstance);

	return (int)message.wParam;
}

//====================================================================
//			## ������ ���ν��� ##
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//====================================================================
//			## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//====================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}