// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
//디버깅용 (주석치면 콘솔창이 사라진다)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
// STL 컨테이너 헤더파일
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "util.h"
using namespace MY_UTIL;

//====================================================================
//			## 내가 만든 헤더파일을 이곳에 추가한다 ##
//====================================================================
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "imageManager.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "timeManager.h"


//====================================================================
//			## 싱글톤을 이곳에 추가한다 ##
//====================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()


//====================================================================
//			## 디파인문 - 메크로 ## (윈도우창 초기화)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("피의 수요일과 함께하는 개발4팀"))
#define WINSTARTX		-1400
#define WINSTARTY		50
#define WINSIZEX		800
#define WINSIZEY		600
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//====================================================================
//			## 메크로함수 ## (클래스 동적할당된 부분 해제)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}


//====================================================================
//			## 전역변수 ## 
//====================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;