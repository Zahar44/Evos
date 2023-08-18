#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "WindowSize.h"
#include "Keyboard.h"

class Camera
{
private:
	glm::mat4 view			= glm::mat4(1.0f);
	glm::mat4 projection	= glm::mat4(1.0f);
	glm::mat4 oprojection	= glm::mat4(1.0f);
	glm::vec3 orientation	= glm::vec3(0.0f, -0.5f, 0.5f);
	glm::vec3 up			= glm::vec3(0.0f, 1.0f, 0.0f);

	float fov				= 45;
	float nearPlane			= 0.1f;
	float farPlane			= 1000.0f;

	float zoom				= 10.0f;
	float zoomPower			= 5.0f;

	float movementSpeed		= 50.0f;
	float fastMovementSpeed = 500.0f;
	float mouseSensitivity	= 0.1f;

	WindowSize windowSize;
public:
	enum Direction
	{
		Forward,
		Backward,
		Right,
		Left
	};

	void updateView(const glm::vec3& position);
	void updateProjection();
	void processMouseScroll(double yoffset);
	void processMouseMovement(double xoffset, double yoffset);
	glm::mat4& getViewMatrix() { return view; };
	glm::mat4& getProjectionMatrix(bool isOrtho) {
		return isOrtho ? getOrthoProjectionMatrix() : getProjectionMatrix();
	};
	glm::mat4& getProjectionMatrix() { return projection; };
	glm::mat4& getOrthoProjectionMatrix() { return oprojection; };
};
