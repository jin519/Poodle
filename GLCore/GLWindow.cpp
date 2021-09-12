#include "GLWindow.h"
#include "GLWindowException.h"
#include <unordered_map>

using namespace std; 

namespace GLCore 
{
	static GLWindow* getGLWindow(GLFWwindow* const pWindow) 
	{
		return reinterpret_cast<GLWindow*>(glfwGetWindowUserPointer(pWindow));
	}

	static void framebufferSizeCallback(
		GLFWwindow* const pWindow, 
		const int width, 
		const int height)
	{
		getGLWindow(pWindow)->getEventHandler().onResize(width, height); 
	}

	static void keyCallback(
		GLFWwindow* const pWindow, 
		const int key, 
		const int scancode, 
		const int action, 
		const int mods)
	{
		getGLWindow(pWindow)->getEventHandler().onKey(key, scancode, action, mods);
	}

	static void mouseButtonCallback(
		GLFWwindow* const pWindow, 
		const int button, 
		const int action, 
		const int mods)
	{
		getGLWindow(pWindow)->getEventHandler().onMouseButton(button, action, mods);
	}

	static void cursorPosCallback(
		GLFWwindow* const pWindow, 
		const double xPos, 
		const double yPos)
	{
		getGLWindow(pWindow)->getEventHandler().onMouseMove(xPos, yPos);
	}

	static void scrollCallback(
		GLFWwindow* const pWindow, 
		const double xOffset, 
		const double yOffset)
	{
		getGLWindow(pWindow)->getEventHandler().onScroll(yOffset);
	}

	GLWindow::GLWindow(
		const int width, 
		const int height, 
		const string_view& title) : 
		__width{ width }, __height{ height }
	{
		__pWindow = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

		if (!__pWindow)
			throw GLWindowException{ "failed to create GLFW window." };

		glfwSetWindowUserPointer(__pWindow, this);

		glfwSetFramebufferSizeCallback(__pWindow, framebufferSizeCallback);
		glfwSetKeyCallback(__pWindow, keyCallback);
		glfwSetMouseButtonCallback(__pWindow, mouseButtonCallback);
		glfwSetCursorPosCallback(__pWindow, cursorPosCallback);
		glfwSetScrollCallback(__pWindow, scrollCallback);
	}

	GLWindow::~GLWindow()
	{
		glfwDestroyWindow(__pWindow);
	}

	/* member function */
	void GLWindow::bind()
	{
		glfwMakeContextCurrent(__pWindow);
	}

	void GLWindow::startMainLoop()
	{
		GLWindow* const pWindow = getGLWindow(__pWindow); 
		static float prevElapsedTime = 0.f;
		bool firstLoop = true;

		while (!glfwWindowShouldClose(__pWindow))
		{
			glfwPollEvents();

			const float elapsedTime = static_cast<float>(glfwGetTime());

			if (firstLoop)
			{
				firstLoop = false;
				pWindow->getEventHandler().onIdle(0.f);
			}
			else
			{
				const float deltaTime = (elapsedTime - prevElapsedTime);
				pWindow->getEventHandler().onIdle(deltaTime);
			}

			prevElapsedTime = elapsedTime;
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

	void GLWindow::showMouseCursor(const bool state)
	{
		if (state)
			glfwSetInputMode(__pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(__pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}