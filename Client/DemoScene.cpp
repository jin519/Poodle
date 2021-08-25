#include <glad/glad.h>
#include "DemoScene.h"

using namespace GLCore; 

DemoScene::DemoScene(GLWindow& window) : Scene{ window }
{
	__init(); 
}

void DemoScene::onKey(
	const int key, 
	const int scancode, 
	const int action, 
	const int mods)
{
	if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS))
		getWindow().setCloseFlag(true); 
}

void DemoScene::onUpdate(const float deltaTime)
{
}

void DemoScene::onRender()
{
}

void DemoScene::onResize(
	const int width, 
	const int height)
{
	__super::onResize(width, height); 
}

void DemoScene::onMouseButton(
	const int button, 
	const int action, 
	const int mods)
{
}

void DemoScene::onMouseMove(
	const double xPos, 
	const double yPos)
{
}

void DemoScene::onScroll(const double delta)
{
}

void DemoScene::__init()
{
	showMouseCursor(true); 

	glfwSwapInterval(1); // VSYNC 0: off, 1: on
	glEnable(GL_DEPTH_TEST);
}