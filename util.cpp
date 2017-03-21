#include "stdafx.h"
#include "util.h"

namespace MY_UTIL
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		
		return sqrtf(x * x + y * y);
	}

	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		float distance = sqrtf(x * x + y * y);
		float angle = acos(x / distance);

		if (endY > startY) angle = PI2 - angle;

		return angle;
	}
};
