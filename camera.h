#pragma once
typedef struct tagCamera
{
	int marginX;
	int marginY;
	int mapWidth;
	int mapHeight;
	int viewStartX;
	int viewStartY;
	int viewWidth;
	int viewHeight;
	int switchViewDelay;

	void viewPortSetting(float targetX, float targetY)
	{
		if (switchViewDelay == 0)
		{
			viewStartX = targetX - viewWidth / 2;
			if (viewStartX + viewWidth > mapWidth) viewStartX = mapWidth - viewWidth;
			if (viewStartX < 0) viewStartX = 0;

			viewStartY = targetY - viewHeight / 2;
			if (viewStartY + viewHeight > mapHeight) viewStartY = mapHeight - viewHeight;
			if (viewStartY < 0) viewStartY = 0;
		}
	}
} CAMERA, *LPCAMERA;