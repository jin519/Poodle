#include <glad/glad.h>
#include "Scene.h"

using namespace GLCore; 

namespace Poodle
{
	/* constructor */
	Scene::Scene(GLWindow& window) : __pWindow(&window)
	{}

	/* member function */
	void Scene::onResize(const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}

	void Scene::onIdle(const float deltaTime)
	{
		onUpdate(deltaTime);
		onRender();
	}
}