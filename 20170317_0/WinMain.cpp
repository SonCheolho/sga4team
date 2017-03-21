//====================================================================
//			## 헤더파일 써준다 ##
//====================================================================
#include "stdafx.h"
#include "mainGame.h"
//====================================================================
//			## 전역변수 써준다 ##
//====================================================================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };

//메인게임 클래스 정적할당
mainGame mg;

//====================================================================
//			## 함수 전방선언 ##
//====================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//====================================================================
//			## 윈도우 메인함수 ##
//====================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//윈메인의 역할
	//1. 윈도우 창 세팅후 화면에 띄우기
	//2. 메세지 루프

	//인스턴스를 전역변수에 담아둔다
	_hInstance = hInstance;

	//WNDCLASS : 윈도우창의 정보를 저장하기 위한 구조체
	//윈도우클래스 구조체 선언후 초기화
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

	//윈도우 클래스 등록
	RegisterClass(&wndClass);

	//윈도우 창 생성
	_hWnd = CreateWindow(
		WINNAME,				//윈도우 클래스의 이름
		WINNAME,				//윈도우 타이틀바 이름
		WS_OVERLAPPEDWINDOW,	//윈도우 스타일
		WINSTARTX,				//윈도우 화면 x좌표
		WINSTARTY,				//윈도우 화면 y좌표
		WINSIZEX,				//윈도우 화면 가로크기
		WINSIZEY,				//윈도우 화면 세로크기
		NULL,					//부모 윈도우
		(HMENU)NULL,			//메뉴핸들
		hInstance,				//인스턴스
		NULL					//윈도우 및 자식 윈도우를 생성하면 지정하고 그렇지 않으면 NULL(우린 걍 NULL사용하면 됨)
	);

	//윈도우 클라이언트영역 정확히 세팅하기 
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//화면에 윈도우 보여주기
	ShowWindow(_hWnd, nCmdShow);

	//메인게임 클래스 초기화
	if (FAILED(mg.init()))
	{
		return 0;
	}

	//MSG : 운영체제에서 발생하는 메세지 정보를 저장하기 위한 구조체
	MSG message;
	//GetMessage : 메세지를 꺼내올 수 있을때까지 멈춰있는 함수
	//PeekMessage : 메세지가 없더라도 리턴되는 함수

	while (true) //게임용
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
	//메세지루프
	while (GetMessage(&message, 0, 0, 0))
	{
		//TranslateMessage : 키보드 입력메시지 처리를 담당
		//입력된 키가 문자키인지 확인후 대문자, 소문자, 한글, 영문
		//WM_CHAR메세지를 발생시킨다
		//DispatchMessage : 윈도우 프로시져에서 전달된 메세지를
		//실제 윈도우로 전달해준다
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/

	//메인게임 클래스 해제
	mg.release();

	//윈도우 클래스 등록해제
	UnregisterClass(WINNAME, hInstance);

	return (int)message.wParam;
}

//====================================================================
//			## 윈도우 프로시져 ##
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//====================================================================
//			## 윈도우 크기 조정 ## (클라이언트 영역의 사이즈를 정확히 잡아준다)
//====================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };
	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);
	//위 렉트 정보로 윈도우 클라이언트 사이즈 세팅
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}