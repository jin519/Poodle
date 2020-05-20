#include "GLInitializer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>

using namespace std;

namespace GLCore 
{
	/* static function */
	bool GLInitializer::initGL(
		const int renderContextVersionMajor,
		const int renderContextVersionMinor,
		const int profileMode)
	{
		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, renderContextVersionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, renderContextVersionMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, profileMode);

		// dummy window 생성 이유: 
		// GLFWwindow는 render context를 관리하는 역할도 수행함. 
		// glad가 opengl의 함수 포인터 목록을 그래픽 드라이버로부터 읽어오기 위해서는 
		// bind된 render context가 있어야 하며, 해당 render context로부터 함수 목록을 읽어옴. 
		// 따라서 opengl 함수 목록을 초기화 하기 위해 GLFWwindow(render context)가 반드시 필요함
		GLFWwindow* pWindow = glfwCreateWindow(1, 1, "dummy", nullptr, nullptr);

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