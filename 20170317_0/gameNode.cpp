#include "stdafx.h"
#include "gameNode.h"

//====================================================================
//			## 초기화 ##
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
		SetTimer(_hWnd, 1, 10, NULL);		//타이머 초기화
		KEYMANAGER->init();					//키매니져 초기화
		RND->init();						//랜덤펑션 초기화
		IMAGEMANAGER->init();				//이미지매니져 초기화
		TXTDATA->init();					//텍스트데이터 초기화
		INIDATA->init();					//INI데이터 초기화
		SCENEMANAGER->init();				//씬매니져 초기화
		TIMEMANAGER->init();				//타임매니져 초기화
	}

	return S_OK;
}
//====================================================================
//			## 해제 ##
//====================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니져 해제, 싱글톤 해제
		KEYMANAGER->release();
		KEYMANAGER->releaseSingleton();
		//랜덤펑션 해제, 싱글톤 해제
		RND->release();
		RND->releaseSingleton();
		//이미지매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//텍스트데이터 싱글톤 해제
		TXTDATA->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->releaseSingleton();
		//씬매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->releaseSingleton();
	}

	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//====================================================================
//			## 업데이트 ##
//====================================================================
void gameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, FALSE);
}

//====================================================================
//			## 렌더 ##
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
	case WM_TIMER:			//타이머 업데이트
		this->update();
		break;
	case WM_PAINT:			//출력에 관한 모든것을 담당하는 메세지(문자, 그림, 도형등등등)
		hdc = BeginPaint(hWnd, &ps);
		//글자 배경 투명화 시키기
		SetBkMode(hdc, TRANSPARENT);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:		//마우스가 움직일때마다 발생되는 메세지
		//_ptMouse.x = static_cast<float>(LOWORD(lParam));
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:		//키보드 및 마우스버튼이 눌렸을때 발생되는 메세지
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:		//소멸자
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}
