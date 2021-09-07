#include "DemoScene.h"
#include "../Poodle/VertexAttributeListFactory.h"
#include "../Poodle/Logger.h"

using namespace std; 
using namespace GLCore; 
using namespace Poodle; 

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
	{
		Logger::commit(SeverityType::INFO, "esc 활성: 프로그램을 종료합니다.");
		getWindow().setCloseFlag(true);
	}
}

void DemoScene::onUpdate(const float deltaTime)
{
}

void DemoScene::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	__pShaderProgram->bind(); 
	__pVao->draw(); 

	getWindow().swapBuffers();
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

	constexpr GLfloat vertices[] = 
	{
		0.f, 0.8f, 0.f,		// position 
		1.f, 0.f, 0.f, 1.f, // color

		-0.4f, -0.8f, 0.f, 
		0.f, 1.f, 0.f, 1.f, 

		0.4f, -0.8f, 0.f,
		0.f, 0.f, 1.f, 1.f
	}; 

	constexpr GLuint indices[] =
	{
		0, 1, 2
	}; 

	__pVao = make_shared<VertexArray>(
		VertexAttributeListFactory::get(VertexAttributeFlag::POS3 | VertexAttributeFlag::COLOR4),
		make_shared<VertexBuffer>(vertices, sizeof(vertices), GL_STATIC_DRAW),
		make_shared<IndexBuffer>(indices, sizeof(indices), GL_STATIC_DRAW),
		static_cast<GLsizei>(size(indices)));

	__pShaderProgram = make_shared<ShaderProgram>(
		"triangle.vert", 
		"triangle.frag");
}