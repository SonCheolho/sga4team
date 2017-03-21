#pragma once
//====================================================================
//			## using namespace MY_UTIL ##
//====================================================================

#define PI 3.141592654f
#define PI2 (PI * 2)

//나중에 이미지 회전시 사용할 매크로상수
#define PI_2 (PI / 2)
#define PI_4 (PI / 4)
#define PI_8 (PI / 8)

namespace MY_UTIL
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
};

