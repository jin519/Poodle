#pragma once

#include "../GLCore/ShaderProgram.h"
#include "../Poodle/Scene.h"
#include "../Poodle/Model.h"
#include "../GLCore/VertexArray.h"
#include "../GLCore/Texture2D.h"

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
	std::unique_ptr<GLCore::ShaderProgram> __pShaderProgram{};

	// FIXME ----------------
	// std::unique_ptr<GLCore::VertexArray> __pVao{};
	// std::unique_ptr<GLCore::Texture2D> __pTexture{};
	std::shared_ptr<Poodle::Mesh> __pMesh{}; 
	// ----------------------

	GLuint __attribFlag; 

	constexpr void __setAttribFlag(const GLuint attribFlag);
	constexpr GLuint __getAttribFlag() const;
	// ----------------------
};

constexpr void DemoScene::__setAttribFlag(const GLuint attribFlag) 
{
	__attribFlag = attribFlag; 
}

constexpr GLuint DemoScene::__getAttribFlag() const 
{
	return __attribFlag; 
}