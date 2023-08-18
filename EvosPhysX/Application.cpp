#include "Application.h"

Application Application::single;

static void errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Application::single.keycallback(window, key, scancode, action, mods);
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		// The cursor entered the content area of the window
	}
	else
	{
		// The cursor left the content area of the window
	}
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Application::single.mouseButtoncallback(window, button, action, mods);
}

static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Application::single.scrollcallback(window, xoffset, yoffset);
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Application::single.cursorPositioncallback(window, xpos, ypos);
}

static void framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
	Application::single.framebufferSizecallback(window, w, h);
}

bool Application::build()
{
	if (!glfwInit()) return false;
	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	window = glfwCreateWindow(640, 480, "E.V.O.S.", NULL, NULL);
	windowSize.setSize(640, 480);
	if (!window) return false;

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_DEPTH_TEST);

	glfwSwapInterval(0);
	Shader::initialize();
	Font::initialize();

	game.initialize();
	renderer.initialize(&camera, game.getWorld());
	camera.updateProjection();
	renderer.updateViewport(windowSize.getSize().x, windowSize.getSize().y);

	return true;
}

void Application::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		timer.update();

		processKeys();
		if (timer.timeAccumulated > game.simulationTime) {
			Metric::start("Simulate MS");
			game.simulate();
			timer.resetAccumulator();
			Metric::end("Simulate MS");
		}

		Metric::start("Update MS");
		game.update(timer.timeDelta);
		Metric::end("Update MS");

		Metric::start("Render MS");
		renderer.render(window);
		Metric::end("Render MS");

		Metric::set("FPS", { 1.0 / timer.timeDelta, 1 });
		Metric::set("MS", { timer.timeDelta * 1000, 1 });

		Metric::swapSnapshots();
		glfwPollEvents();
	}
}

void Application::processKeys()
{
}

Application::~Application()
{
	if (window) glfwDestroyWindow(window);
	Shader::destroy();
	Font::destroy();

	glfwTerminate();
}

void Application::start()
{
	if (single.build())
		single.loop();
}

void Application::keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_RELEASE)
		keyboard.setKeyIsPressed(key, action == GLFW_PRESS);

	if (action == GLFW_PRESS) {
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
	}
}

void Application::mouseButtoncallback(GLFWwindow* window, int button, int action, int mods)
{
	mouse.setKeyIsPressed(button, action == GLFW_PRESS);
}

void Application::scrollcallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}

void Application::cursorPositioncallback(GLFWwindow* window, double xpos, double ypos)
{
	mouse.setPosition(xpos, ypos);

	if (mouse.isKeyPressed(GLFW_MOUSE_BUTTON_1)) {
		auto offset = mouse.getPositionOffset();
		camera.processMouseMovement(offset.x, offset.y);
	}
}

void Application::framebufferSizecallback(GLFWwindow* window, int w, int h)
{
	windowSize.setSize(w, h);
	camera.updateProjection();
	renderer.updateViewport(w, h);
}
