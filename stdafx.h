// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//
#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <Windows.h>
//������ (�ּ�ġ�� �ܼ�â�� �������)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
// STL �����̳� �������
#include <string>
#include <vector>
#include <map>
using namespace std;
#include "util.h"
using namespace MY_UTIL;

//====================================================================
//			## ���� ���� ��������� �̰��� �߰��Ѵ� ##
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
//			## �̱����� �̰��� �߰��Ѵ� ##
//====================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TXTDATA txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()


//====================================================================
//			## �����ι� - ��ũ�� ## (������â �ʱ�ȭ)
//====================================================================
#define WINNAME (LPTSTR)(TEXT("���� �����ϰ� �Բ��ϴ� ����4��"))
#define WINSTARTX		-1400
#define WINSTARTY		50
#define WINSIZEX		800
#define WINSIZEY		600
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//====================================================================
//			## ��ũ���Լ� ## (Ŭ���� �����Ҵ�� �κ� ����)
//====================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}


//====================================================================
//			## �������� ## 
//====================================================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;