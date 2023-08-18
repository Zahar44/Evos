#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "World.h"
#include "UIModule.h"

class Renderer
{
private:
	Camera*		camera		= NULL;
	World*		world		= NULL;
	UIModule	ui;
	
	int renderHalfSize		= 10;

	void updateProjectionMatrix();
	void renderChunk(int xOffset, int zOffset, float cameraChunkPosX, float cameraChunkPosZ);
public:
	void initialize(Camera* camera, World* world);
	void render(GLFWwindow* window);
	void updateViewport(int width, int height);
};
