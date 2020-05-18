#include "GLWindow.h"
#include "GLWindowException.h"
#include <unordered_map>

using namespace std;

/* global function */
static unordered_map<GLFWwindow*, GLWindow*>& getWindowMap()
{
	static unordered_map<GLFWwindow*, GLWindow*> windowMap;
	return windowMap;
}

static void framebufferSizeCallback(GLFWwindow* const pWindow, const int width, const int height)
{
	getWindowMap().at(pWindow)->getEventHandler().onResize(width, height);
}

static void keyCallback(GLFWwindow* const pWindow, const int key, const int scancode, const int action, const int mods)
{
	getWindowMap().at(pWindow)->getEventHandler().onKey(key, scancode, action, mods);
}

/* constructor */
GLWindow::GLWindow(
	const int width,
	const int height,
	const char* const title) : 
	__width(width), __height(height)
{
	__pWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!__pWindow)
		throw GLWindowException("Failed to create GLFW window.");

	getWindowMap().emplace(__pWindow, this);

	glfwSetFramebufferSizeCallback(__pWindow, framebufferSizeCallback);
	glfwSetKeyCallback(__pWindow, keyCallback);
}

/* destructor */
GLWindow::~GLWindow() 
{
	glfwDestroyWindow(__pWindow);
	getWindowMap().erase(__pWindow);
}

/* member function */
void GLWindow::bind() 
{
	glfwMakeContextCurrent(__pWindow);
}
	
void GLWindow::startMainLoop() 
{
	GLWindow* const pWindow = getWindowMap().at(__pWindow);
	static float prevElapsedTime = 0.f;
	bool firstLoop = true;

	while (!glfwWindowShouldClose(__pWindow))
	{
		glfwPollEvents();

		const float ELAPSED_TIME = static_cast<float>(glfwGetTime());

		if (firstLoop)
		{
			pWindow->getEventHandler().onIdle(0.f);
			firstLoop = false;
		}
		else
		{
			const float DELTA_TIME = (ELAPSED_TIME - prevElapsedTime);
			pWindow->getEventHandler().onIdle(DELTA_TIME);
		}

		prevElapsedTime = ELAPSED_TIME;
	}
}

void GLWindow::setCloseFlag(const bool flag) 
{
	glfwSetWindowShouldClose(__pWindow, flag);
}
	
void GLWindow::swapBuffers() 
{
	glfwSwapBuffers(__pWindow);
}