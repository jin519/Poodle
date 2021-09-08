#pragma once

#include "../GLCore/GLWindow.h"

namespace Poodle 
{
	class Scene : public GLCore::GLWindowEventHandler 
	{
	public:
		explicit Scene(GLCore::GLWindow& window); 

		virtual ~Scene() = default; 
		
		virtual void onUpdate(const float deltaTime) = 0;
		
		virtual void onRender() = 0;
		
		virtual void onIdle(const float deltaTime) override;
		
		virtual void onResize(
			const int width, 
			const int height) override;

		void showMouseCursor(const bool state);
		
		constexpr GLCore::GLWindow& getWindow() const;

	private:
		GLCore::GLWindow* __pWindow = nullptr;
		float __elapsedTime = 0.f;
	};

	constexpr GLCore::GLWindow& Scene::getWindow() const
	{
		return *__pWindow;
	}
}