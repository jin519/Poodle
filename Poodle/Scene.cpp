#include <glad/glad.h>
#include "Scene.h"

using namespace GLCore; 

namespace Poodle 
{
	Scene::Scene(GLCore::GLWindow& window) :
		__pWindow{ &window }
	{}

	void Scene::onIdle(const float deltaTime)
	{
		onUpdate(deltaTime);
		onRender();
	}

	void Scene::onResize(
		const int width, 
		const int height)
	{
		glViewport(0, 0, width, height);
	}

	void Scene::showMouseCursor(const bool state)
	{
		__pWindow->showMouseCursor(state);
	}
}