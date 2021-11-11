#pragma once
#include "singletonBase.h"
#include "timer.h"

class timeManager : public singletonBase<timeManager>
{
private:
	timer* _timer;

	float _startTime;
	float _recordTime;
	bool _startRecord;

public:
	timeManager();
	~timeManager();

	HRESULT init();
	void release();
	void update(float lock = 0.0f);
	void render();

	void start_record();

	inline float getElapsedTime() const { return _timer->getElapsedTime(); }
	inline float getWorldTime() const { return _timer->getWorldTime(); }
	inline int getFrameRate(void) const { return _timer->getFrameRate(); }
	inline float getRecordTime() const { return _recordTime; }
};
			
