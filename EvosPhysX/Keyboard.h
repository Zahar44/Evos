#pragma once
#include <map>

class Keyboard
{
private:
	static std::map<int, bool> _isKeyPressed;
public:
	bool isKeyPressed(int key) {
		std::map<int, bool>::iterator it = _isKeyPressed.find(key);
		if (it == _isKeyPressed.end()) return false;

		return _isKeyPressed[key];
	};

	void setKeyIsPressed(int key, bool pressed) {
		_isKeyPressed[key] = pressed;
	}
};
