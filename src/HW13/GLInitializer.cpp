#include "GLInitializer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>

using namespace std;

/* static function */
bool GLInitializer::initGL(
	const int renderContextVersionMajor,
	const int renderContextVersionMinor,
	const int profileMode) 
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, renderContextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, renderContextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, profileMode);

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