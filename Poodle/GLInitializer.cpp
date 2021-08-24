#include "GLInitializer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GLCore 
{
	bool GLInitializer::initGL(
		const int majorVersion,
		const int minorVersion) 
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		/*
			dummy window ���� ����: 
			GLFWwindow�� render context�� �����ϴ� ���ҵ� ������.
			glad�� opengl�� �Լ� ������ ����� �׷��� ����̹��κ��� �о���� ���ؼ���
			bind�� render context�� �־�� �ϸ�, �ش� render context�κ��� �Լ� ����� �о��.
			���� opengl �Լ� ����� �ʱ�ȭ �ϱ� ���� GLFWwindow(render context)�� �ݵ�� �ʿ���.
		*/
		GLFWwindow* const pWindow = glfwCreateWindow(1, 1, "dummy", nullptr, nullptr);

		if (!pWindow)
		{
			releaseGL();
			return false;
		}

		glfwMakeContextCurrent(pWindow);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			releaseGL();
			return false;
		}

		glfwDestroyWindow(pWindow);

		return true;
	}

	void GLInitializer::releaseGL() 
	{
		glfwTerminate();
	}
}