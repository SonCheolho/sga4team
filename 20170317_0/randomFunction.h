#pragma once
#include "singletonBase.h"
//====================================================================
//			## randdomFunction ## (�ʿ��� �κ��� ���� �߰��ض�!!!)
//====================================================================
class randomFunction : public singletonBase <randomFunction>
{
public:
	//���ǻ��� ���� getFromIntTo(0, 100)�� ����ϴ� ��� ������
	//0~���� �����ϴ� ���� getInt()�� ����Ұ�!!!
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
		//�����õ� �ʱ�ȭ
		srand(GetTickCount());
		return S_OK; 
	}
	void release(void) {}

	randomFunction() {}
	~randomFunction() {}
};
