#pragma once

#include "../GLCore/ShaderProgram.h"
#include "../Poodle/Scene.h"
#include "../Poodle/Model.h"
#include "../Poodle/PerspectiveCamera.h"
#include "../GLCore/VertexArray.h" // FIXME
#include "../GLCore/Texture2D.h" // FIXME

class DemoScene : public Poodle::Scene 
{
public:
	explicit DemoScene(GLCore::GLWindow& window);
	virtual ~DemoScene(); 

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

	std::unique_ptr<Poodle::Model> __pModel{};
	std::shared_ptr<GLCore::ShaderProgram> __pShaderProgram{};
	std::unique_ptr<Poodle::PerspectiveCamera> __pCamera{};

	// FIXME ----------------
	// std::unique_ptr<GLCore::VertexArray> __pVao{};
	// std::unique_ptr<GLCore::Texture2D> __pTexture{};
	// ----------------------

	bool __wPressed{ false };
	bool __sPressed{ false }; 
	bool __aPressed{ false }; 
	bool __dPressed{ false }; 
	bool __qPressed{ false }; 
	bool __ePressed{ false }; 
};