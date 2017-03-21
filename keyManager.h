#pragma once
#include "singletonBase.h"
#include <bitset>

using namespace std;

//============================================================================
//		## keyManager ## (키메니져)
//============================================================================

#define KEYMAX 256

class keyManager : public singletonBase<keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init(void);

	//키가 한번만 눌렸냐?
	bool isOnceKeyDown(int key);
	//키가 한번 눌렀다가 띄었냐?
	bool isOnceKeyUp(int key);
	//키가 계속 눌려있냐?
	bool isStayKeyDown(int key);
	//키가 토글키냐?
	bool isToggleKey(int key);

	keyManager();
	~keyManager();
};

