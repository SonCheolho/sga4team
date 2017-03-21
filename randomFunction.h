#pragma once
#include "singletonBase.h"
//============================================================================
//		## randomFunction ## (rand() 함수)
//============================================================================
class randomFunction : public singletonBase<randomFunction>
{
public:
	randomFunction()
	{
		srand(GetTickCount());
	}
	~randomFunction(){}

	//getInt
	inline int getInt(int num) { return rand() % num; }
	//getFromIntTo => fromNum이 0이상이여야한다.
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return fromNum + rand() % (toNum - fromNum + 1);
	}

	//getFloat
	inline float getFloat(float num) { return (float)rand() / (float)RAND_MAX * num; }
	//getFromFloatTo => fromNum이 0이상이여야한다.
	inline float getFromFloatTo(float fromNum, float toNum)
	{
		return fromNum + ((float)rand() / (float)RAND_MAX) * (toNum - fromNum + 1);
	}
};

