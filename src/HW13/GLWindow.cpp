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

static void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	getWindowMap().at(pWindow)->getEventHandler().onResize(width, height);
}

static void keyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
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
	setCloseFlag(true);
	getWindowMap().erase(__pWindow);
}

/* member function */
void GLWindow::bind() 
{
	glfwMakeContextCurrent(__pWindow);
}
	
void GLWindow::startMainLoop() 
{
	while (!glfwWindowShouldClose(__pWindow))
	{
		glfwPollEvents();
		getWindowMap().at(__pWindow)->getEventHandler().onIdle(static_cast<float>(glfwGetTime()));
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