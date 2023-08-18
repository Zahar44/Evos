#pragma once
#include <map>
#include <glm/glm.hpp>

class Mouse
{
private:
	static std::map<int, bool> _isKeyPressed;
	static glm::dvec2 lastPosition;
	static glm::dvec2 position;
public:
	bool isKeyPressed(int key) {
		std::map<int, bool>::iterator it = _isKeyPressed.find(key);
		if (it == _isKeyPressed.end()) return false;

		return _isKeyPressed[key];
	};

	void setKeyIsPressed(int key, bool pressed) {
		_isKeyPressed[key] = pressed;
	}

	void setPosition(double x, double y) {
		lastPosition = position;
		position.x = x;
		position.y = y;
	}

	const glm::dvec2& getPosition() { return position; }
	const glm::dvec2 getPositionOffset() { return position - lastPosition; }
};
