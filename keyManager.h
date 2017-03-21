#pragma once
#include "singletonBase.h"
#include <bitset>

using namespace std;

//============================================================================
//		## keyManager ## (Ű�޴���)
//============================================================================

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init(void);

	//Ű�� �ѹ��� ���ȳ�?
	bool isOnceKeyDown(int key);
	//Ű�� �ѹ� �����ٰ� �����?
	bool isOnceKeyUp(int key);
	//Ű�� ��� �����ֳ�?
	bool isStayKeyDown(int key);
	//Ű�� ���Ű��?
	bool isToggleKey(int key);

	keyManager();
	~keyManager();
};

