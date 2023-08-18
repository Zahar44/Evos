#pragma once
#include <iostream>
#include "Game.h"
#include "Renderer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "WindowSize.h"
#include "World.h"
#include "Font.h"
#include "Metric.h"

struct ApplicationTimer {
	double lastUpdateTime = 0.0;
	double timeAccumulated = 0.0;
	double timeDelta = 0.0;

	void update() {
		auto now = glfwGetTime();
		timeDelta = now - lastUpdateTime;
		lastUpdateTime = now;
		timeAccumulated += timeDelta;
	}

	void resetAccumulator() {
		timeAccumulated = 0.0;
	}
};

class Application
{
private:
	Game			 game;
	Renderer		 renderer;
	ApplicationTimer timer;
	GLFWwindow*		 window = NULL;
	Camera			 camera;
	Keyboard		 keyboard;
	Mouse			 mouse;
	WindowSize		 windowSize;

	bool build();
	void loop();
	void processKeys();
public:
	static Application single;
	~Application();

	static void start();

	void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseButtoncallback(GLFWwindow* window, int button, int action, int mods);
	void scrollcallback(GLFWwindow* window, double xoffset, double yoffset);
	void cursorPositioncallback(GLFWwindow* window, double xpos, double ypos);
	void framebufferSizecallback(GLFWwindow* window, int w, int h);
};
