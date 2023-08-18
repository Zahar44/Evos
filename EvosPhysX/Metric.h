#pragma once
#include <map>
#include <GLFW/glfw3.h>

class MetricSnapshot {
private:
	double _startedAt;
	double _endedAt;
	double _elapsed;
	int _scale;
public:
	MetricSnapshot(int scale = 1000) :
		_startedAt(glfwGetTime()), _endedAt(0), _elapsed(0), _scale(scale) {}
	MetricSnapshot(double elapsed, int scale = 1000) :
		_startedAt(0), _endedAt(glfwGetTime()), _elapsed(elapsed), _scale(scale) {}

	double end() {
		_endedAt = glfwGetTime();
		return elapsed();
	}

	double elapsed() {
		if (_elapsed == 0) {
			_elapsed = _endedAt > 0 ? _endedAt - _startedAt : 0;
		}
		return _elapsed * _scale;
	}

	double startedAt() {
		return _startedAt;
	}

	double endedAt() {
		return _endedAt;
	}
};

class Metric {
private:
	static std::map<const char*, MetricSnapshot> snapshots1;
	static std::map<const char*, MetricSnapshot> snapshots2;
	static bool snapshotsSwapped;
	static double lastTimeSwapped;
	static float swapInterval;
	Metric() {}
public:
	static void start(const char* name, int scale = 1000) {
		Metric::getSnapshots()[name] = MetricSnapshot(scale);
	};
	static void end(const char* name) {
		Metric::getSnapshots()[name].end();
	}
	static void set(const char* name, MetricSnapshot snapshot) {
		Metric::getSnapshots()[name] = snapshot;
	}

	static void swapSnapshots() {
		auto now = glfwGetTime();
		if (now - lastTimeSwapped < swapInterval) {
			return;
		}

		lastTimeSwapped = now;
		snapshotsSwapped = !snapshotsSwapped;
	}

	static std::map<const char*, MetricSnapshot>& getLastSnapshots() {
		return !snapshotsSwapped ? Metric::snapshots2 : Metric::snapshots1;
	}

	static std::map<const char*, MetricSnapshot>& getSnapshots() {
		return snapshotsSwapped ? Metric::snapshots2 : Metric::snapshots1;
	}
};
