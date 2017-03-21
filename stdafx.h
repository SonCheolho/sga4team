// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <Windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
// ���ֻ���ϴ� STL
#include <string>
#include <vector>
#include <map>

//============================================================================
//		## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//============================================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "util.h"
#include "camera.h"

//============================================================================
//		## �̱����� �߰��Ѵ� ##
//============================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()

//==================================================================
//		## ���ӽ����̽� �߰��Ѵ� ##
//==================================================================
using namespace std;
using namespace MY_UTIL;

//============================================================================
//		## �����ι� ## (������â �ʱ�ȭ)
//============================================================================
#define WINNAME (LPTSTR)(TEXT("MegamanX6"))
#define WINSTARTX 100
#define WINSTARTY 100
#define WINSIZEX 1000
#define WINSIZEY 800
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//============================================================================
//		## ��ũ���Լ� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//============================================================================
#define SAFE_DELETE(p) {if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); (p) = NULL;}}

//============================================================================
//		## �������� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//============================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
