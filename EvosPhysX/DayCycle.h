#pragma once
#include <cmath>

class DayCycle {
private:
	float currentTime;
	float dayTime;
	float nightTime;
	float cycleTime;
public:
	enum State {
		Day,
		Night
	};

	DayCycle(float _cycleTime, float _dayPersent):
		cycleTime(_cycleTime), currentTime(0) {
		dayTime = cycleTime * (1.0f - _dayPersent);
		nightTime = cycleTime - dayTime;
	};

	void update(float delta) {
		currentTime = fmodf(currentTime + delta, cycleTime);
	}

	State getState(float& persent) {
		if (currentTime < dayTime) {
			persent = currentTime / dayTime;
			return State::Day;
		}

		persent = (currentTime - dayTime) / nightTime;
		return State::Night;
	}
};
