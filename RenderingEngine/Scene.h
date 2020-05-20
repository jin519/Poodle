#pragma once

#include "GLWindowEventHandler.h"
#include "GLWindow.h"

namespace Poodle
{
	class Scene abstract : public GLCore::GLWindowEventHandler
	{
	public:
		/* constructor */
		explicit Scene(GLCore::GLWindow& window);

		/* member function */
		constexpr GLCore::GLWindow& getWindow() const;
		virtual void onUpdate(const float deltaTime) = 0;
		virtual void onRender() = 0;
		virtual void onResize(const int width, const int height) override;
		virtual void onIdle(const float deltaTime) override;

	private:
		/* member variable */
		GLCore::GLWindow* __pWindow = nullptr;
		float __elapsedTime = 0.f;
	};

	constexpr GLCore::GLWindow& Scene::getWindow() const
	{
		return *__pWindow;
	}
}