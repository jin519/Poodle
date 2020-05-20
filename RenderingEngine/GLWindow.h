#pragma once

#include <GLFW/glfw3.h>
#include "GLWindowEventHandler.h"

namespace GLCore 
{
	class GLWindow
	{
	public:
		/* constructor */
		GLWindow(
			const int width,
			const int height,
			const char* const title);

		/* destructor */
		virtual ~GLWindow();

		/* member function */
		void bind();
		constexpr int getWidth() const;
		constexpr int getHeight() const;
		constexpr GLWindowEventHandler& getEventHandler() const;
		constexpr void setEventHandler(GLWindowEventHandler& eventHandler);
		void startMainLoop();
		void setCloseFlag(const bool flag);
		void swapBuffers();

	private:
		/* member variable */
		int __width;
		int __height;
		GLFWwindow* __pWindow = nullptr;
		GLWindowEventHandler* __pEventHandler = nullptr;
	};

	/* member function */
	constexpr int GLWindow::getWidth() const
	{
		return __width;
	}

	constexpr int GLWindow::getHeight() const
	{
		return __height;
	}

	constexpr GLWindowEventHandler& GLWindow::getEventHandler() const
	{
		return *__pEventHandler;
	}

	constexpr void GLWindow::setEventHandler(GLWindowEventHandler& eventHandler)
	{
		__pEventHandler = &eventHandler;
	}
}