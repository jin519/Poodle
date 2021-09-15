#include "DemoScene.h"
#include "../Poodle/VertexAttributeListFactory.h"
#include "../Poodle/Logger.h"
#include "../Poodle/ModelLoader.h"
#include "../GLCore/TextureUtil.h" // FIXME

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
{}

void DemoScene::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	__pTexture->activate(0); 
	__pShaderProgram->setUniform1ui("attribFlag", __getAttribFlag()); 

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

	// TODO
	// __pModel = ModelLoader::load("resource/Nanosuit/scene.gltf");

	const vector<vector<GLfloat>> vboList
	{
		{ // position
			0.f, 0.8f, 0.f,
			-0.4f, -0.8f, 0.f,
			0.4f, -0.8f, 0.f
		},
		{ // texcoord
			0.5f, 1.f, 
			0.f, 0.f, 
			1.f, 0.f
		},
		{ // color
			1.f, 0.f, 0.f, 1.f,
			0.f, 1.f, 0.f, 1.f,
			0.f, 0.f, 1.f, 1.f
		} 
	};

	constexpr GLuint indices[]
	{
		0, 1, 2
	}; 

	constexpr VertexAttributeFlag attribFlag{ VertexAttributeFlag::POSITION | VertexAttributeFlag::TEXCOORD | VertexAttributeFlag::COLOR };

	__setAttribFlag(GLuint(attribFlag)); // FIXME

	unordered_map<VertexAttribute, std::unique_ptr<VertexBuffer>> attrib2VertexBufferMap;
	{
		size_t i = 0ULL;

		for (const VertexAttribute& attrib : VertexAttributeListFactory::get(attribFlag))
		{
			const vector<GLfloat>& vbo = vboList[i++];

			attrib2VertexBufferMap.emplace(
				attrib, make_unique<VertexBuffer>(vbo.data(), (sizeof(GLfloat) * vbo.size()), GL_STATIC_DRAW));
		}
	}

	__pVao = make_unique<VertexArray>(
		move(attrib2VertexBufferMap), 
		make_unique<IndexBuffer>(indices, sizeof(indices), GL_STATIC_DRAW), 
		static_cast<GLsizei>(size(indices)));

	__pTexture = unique_ptr<Texture2D>{ TextureUtil::createTexture2DFromImage("resource/Nanosuit/textures/Body_normal.png") };
	__pTexture->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
	__pTexture->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
	__pTexture->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	__pTexture->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	__pShaderProgram = make_unique<ShaderProgram>(
		"shaders/triangle.vert", 
		"shaders/triangle.frag");
}