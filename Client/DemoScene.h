#pragma once

#include "../GLCore/ShaderProgram.h"
#include "../Poodle/Scene.h"
#include "../GLCore/VertexArray.h"

class DemoScene : public Poodle::Scene 
{
public:
	explicit DemoScene(GLCore::GLWindow& window);

	virtual void onKey(
		const int key, 
		const int scancode, 
		const int action, 
		const int mods) override;

	virtual void onUpdate(const float deltaTime) override;
	
	virtual void onRender() override;
	
	virtual void onResize(
		const int width, 
		const int height) override;

	virtual void onMouseButton(
		const int button, 
		const int action, 
		const int mods) override;

	virtual void onMouseMove(
		const double xPos, 
		const double yPos) override;

	virtual void onScroll(const double delta) override;

private:
	void __init();

	std::shared_ptr<GLCore::VertexArray> __pVao;
	std::shared_ptr<GLCore::ShaderProgram> __pShaderProgram;
};