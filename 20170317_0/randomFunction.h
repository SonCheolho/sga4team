#pragma once
#include "singletonBase.h"
//====================================================================
//			## randdomFunction ## (필요한 부분은 직접 추가해라!!!)
//====================================================================
class randomFunction : public singletonBase <randomFunction>
{
public:
	//주의사항 만약 getFromIntTo(0, 100)을 사용하는 경우 뻥난다
	//0~부터 시작하는 값은 getInt()를 사용할것!!!
	//getInt
	inline int getInt(int num) { return rand() % num; }
	//getFromIntTo
	inline int getFromIntTo(int startNum, int endNum)
	{
		return rand() % (endNum - startNum + 1) + startNum;
	}

	//getFloat
	inline float getFloat(float num)
	{
		return ((float)rand() / (float)RAND_MAX) * num;
	}
	//getFromFloatTo
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}

public:
	HRESULT init(void) 
	{	
		//랜덤시드 초기화
		srand(GetTickCount());
		return S_OK; 
	}
	void release(void) {}

	randomFunction() {}
	~randomFunction() {}
};
