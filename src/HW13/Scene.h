#pragma once

#include "GLWindowEventHandler.h"
#include "GLWindow.h"

class Scene abstract : public GLWindowEventHandler
{
public:
	/* constructor */
	explicit Scene(GLWindow& window);

	/* member function */
	constexpr GLWindow& getWindow() const;
	virtual void onUpdate(const float deltaTime) = 0;
	virtual void onRender() = 0;
	virtual void onResize(const int width, const int height) override;
	virtual void onIdle(const float deltaTime) override;

private:
	/* member variable */
	GLWindow* __pWindow = nullptr;
};

constexpr GLWindow& Scene::getWindow() const 
{
	return *__pWindow;
}