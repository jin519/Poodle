#pragma once

#include <string_view>
#include <GLFW/glfw3.h>
#include "GLWindowEventHandler.h"

namespace GLCore 
{
	class GLWindow 
	{
	public:
		GLWindow(
			const int width,
			const int height,
			const std::string_view& title);

		virtual ~GLWindow(); 

		void bind();
		void startMainLoop();
		void setCloseFlag(const bool flag);
		void swapBuffers();
		void showMouseCursor(const bool state);

		constexpr int getWidth() const;
		constexpr int getHeight() const;
		constexpr GLWindowEventHandler& getEventHandler() const;
		constexpr void setEventHandler(GLWindowEventHandler& eventHandler);

	private:
		int __width;
		int __height;

		GLFWwindow* __pWindow = nullptr;
		GLWindowEventHandler* __pEventHandler = nullptr;
	};

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