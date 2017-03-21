#include "stdafx.h"
#include "gameNode.h"

//====================================================================
//			## �ʱ�ȭ ##
//====================================================================
HRESULT gameNode::init(void)
{
	return S_OK;
}
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;
	
	if (managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);		//Ÿ�̸� �ʱ�ȭ
		KEYMANAGER->init();					//Ű�Ŵ��� �ʱ�ȭ
		RND->init();						//������� �ʱ�ȭ
		IMAGEMANAGER->init();				//�̹����Ŵ��� �ʱ�ȭ
		TXTDATA->init();					//�ؽ�Ʈ������ �ʱ�ȭ
		INIDATA->init();					//INI������ �ʱ�ȭ
		SCENEMANAGER->init();				//���Ŵ��� �ʱ�ȭ
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� �ʱ�ȭ
	}

	return S_OK;
}
//====================================================================
//			## ���� ##
//====================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);
		//Ű�Ŵ��� ����, �̱��� ����
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//������� ����, �̱��� ����
		RND->release();
		RND->releaseSingleton();
		//�̹����Ŵ��� ����, �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//�ؽ�Ʈ������ �̱��� ����
		TXTDATA->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->releaseSingleton();
		//���Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->releaseSingleton();
	}

	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//====================================================================
//			## ������Ʈ ##
//====================================================================
void gameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, FALSE);
}

//====================================================================
//			## ���� ##
//====================================================================
void gameNode::render(void)
{
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:			//Ÿ�̸� ������Ʈ
		this->update();
		break;
	case WM_PAINT:			//��¿� ���� ������ ����ϴ� �޼���(����, �׸�, ��������)
		hdc = BeginPaint(hWnd, &ps);
		//���� ��� ����ȭ ��Ű��
		SetBkMode(hdc, TRANSPARENT);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:		//���콺�� �����϶����� �߻��Ǵ� �޼���
		//_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		//Ű���� �� ���콺��ư�� �������� �߻��Ǵ� �޼���
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		//�Ҹ���
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
