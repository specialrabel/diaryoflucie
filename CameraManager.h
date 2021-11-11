#pragma once
#include "singletonBase.h"

class CameraManager : public singletonBase<CameraManager>
{
private:
	float mapsize_x, mapsize_y;
	float camera_x, camera_y;
	float _x, _y;

public:

	CameraManager();
	~CameraManager();

	HRESULT init(float width, float height);
	void release();

	//카메라 위치 갱신
	inline float get_camera_x() { return _x; }
	inline float get_camera_y() { return _y; }
	inline void set_camera(int x, int y) { camera_x = x, camera_y = y; }

	void updateScreen(float standardX, float standardY, float ratioX = 0.5f, float ratioY = 0.5f);
	void scaleScreen(float destX, float destY, float x = 1.0f, float y = 1.0f);
	void scaleScreen_end();

	float getMapSizeX() { return mapsize_x; }
	float getMapSizeY() { return mapsize_y; }

};

