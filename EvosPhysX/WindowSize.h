#pragma once
#include <glm/glm.hpp>

class WindowSize
{
private:
	static glm::ivec2 size;
public:
	void setSize(int w, int h) {
		size.x = w;
		size.y = h;
	}

	glm::ivec2 getSize() {
		return size;
	}

	float getRatio() {
		return (float)size.x / (float)size.y;
	}
};
