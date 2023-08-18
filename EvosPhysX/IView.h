#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

class IView {
public:
	virtual void draw() = 0;
};
