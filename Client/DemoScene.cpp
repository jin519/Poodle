#include "DemoScene.h"
#include "../Poodle/VertexAttributeListFactory.h"
#include "../Poodle/Logger.h"
#include "../Poodle/ModelLoader.h"

using namespace std; 
using namespace GLCore; 
using namespace Poodle; 

DemoScene::DemoScene(GLWindow& window) : Scene{ window }
{
	__init(); 
}

DemoScene::~DemoScene()
{
	__pModel.reset(); 
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

	if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "w 활성: 카메라를 앞으로 이동합니다."); 
		__wPressed = true;
	}

	if ((key == GLFW_KEY_W) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "w 해제");
		__wPressed = false;
	}

	if ((key == GLFW_KEY_S) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "s 활성: 카메라를 뒤로 이동합니다.");
		__sPressed = true;
	}

	if ((key == GLFW_KEY_S) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "s 해제");
		__sPressed = false;
	}

	if ((key == GLFW_KEY_A) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "a 활성: 카메라를 오른쪽으로 이동합니다.");
		__aPressed = true;
	}

	if ((key == GLFW_KEY_A) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "a 해제");
		__aPressed = false;
	}

	if ((key == GLFW_KEY_D) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "d 활성: 카메라를 왼쪽으로 이동합니다.");
		__dPressed = true;
	}

	if ((key == GLFW_KEY_D) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "d 해제");
		__dPressed = false;
	}

	if ((key == GLFW_KEY_Q) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "q 활성: 카메라를 위로 이동합니다.");
		__qPressed = true;
	}

	if ((key == GLFW_KEY_Q) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "q 해제");
		__qPressed = false;
	}

	if ((key == GLFW_KEY_E) && (action == GLFW_PRESS))
	{
		Logger::commit(SeverityType::INFO, "e 활성: 카메라를 아래로 이동합니다.");
		__ePressed = true;
	}

	if ((key == GLFW_KEY_E) && (action == GLFW_RELEASE))
	{
		Logger::commit(SeverityType::INFO, "e 해제");
		__ePressed = false;
	}
}

void DemoScene::onUpdate(const float deltaTime)
{
	Transform& cameraTransform = __pCamera->getTransform(); 
	const GLfloat translationStep = (deltaTime * Constant::Camera::translationStep);

	if (__wPressed)
		cameraTransform.advanceZ(-translationStep);
	if (__sPressed)
		cameraTransform.advanceZ(translationStep);
	if (__aPressed)
		cameraTransform.advanceX(translationStep);
	if (__dPressed)
		cameraTransform.advanceX(-translationStep);
	if (__qPressed)
		cameraTransform.advanceY(translationStep);
	if (__ePressed)
		cameraTransform.advanceY(-translationStep);

	__pCamera->update(); 
}

void DemoScene::onRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	__pShaderProgram->setUniformMatrix4f("viewMat", __pCamera->getViewMatrix());
	__pShaderProgram->setUniformMatrix4f("projectionMat", __pCamera->getProjectionMatrix());

	for (auto& pMesh : __pModel->getMeshes()) 
	{
		__pShaderProgram->setUniformMatrix4f("modelMat", __pModel->getTransform().getModelMatrix()); 
		__pShaderProgram->setUniform1ui("attribFlag", GLuint(pMesh->getAttribFlag()));
		
		for (const auto& pSubmeshInfo : pMesh->getSubmeshInfo())
		{
			const int materialIndex = pSubmeshInfo->getMaterialIndex();
			const shared_ptr<Material>& pMaterial = __pModel->getMaterial(materialIndex);

			const int diffuseTexIndex = pMaterial->getDiffuseTextureIndex(); 
			const bool hasDiffuseTex = (diffuseTexIndex >= 0); 

			if (hasDiffuseTex)
			{
				Texture2D& diffuseTex = *__pModel->getTexture(diffuseTexIndex);
				diffuseTex.activate(diffuseTexIndex);

				__pShaderProgram->setUniform1i("hasDiffuseTex", hasDiffuseTex);
				__pShaderProgram->setUniform1i("diffuseTex", diffuseTexIndex);
			}

			const GLsizei count = GLsizei(pSubmeshInfo->getNumIndices()); 
			const size_t first = size_t(pSubmeshInfo->getIndexOffset());

			pMesh->draw(count, first); 
		}
	}

	getWindow().swapBuffers();
}

void DemoScene::onResize(
	const int width, 
	const int height)
{
	__super::onResize(width, height); 
	__pCamera->setAspectRatio(width, height); 
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

	__pModel = ModelLoader::load("resource/Nanosuit/scene.gltf");
	__pModel->getTransform().setScale(0.1f); 

	__pCamera = make_unique<PerspectiveCamera>(); 
	__pCamera->setNear(0.1f);
	__pCamera->setFar(200.f);
	__pCamera->getTransform().advanceZ(70.f);

	__pShaderProgram = make_shared<ShaderProgram>(
		"shaders/triangle.vert", 
		"shaders/triangle.frag");
}