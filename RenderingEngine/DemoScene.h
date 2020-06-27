#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include "Scene.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "PerspectiveCamera.h"
#include "Cube.h"

class DemoScene : public Poodle::Scene 
{
public:
	/* constructor */
	explicit DemoScene(GLCore::GLWindow& window);

	/* member function */
	virtual void onKey(const int key, const int scancode, const int action, const int mods) override;
	virtual void onUpdate(const float deltaTime) override;
	virtual void onRender() override;
	virtual void onResize(const int width, const int height) override;
	virtual void onMouseButton(const int button, const int action, const int mods) override;
	virtual void onMouseMove(const double xPos, const double yPos) override;

private:
	/* member function */
	void __init();
	void __createCubes();

	/* member variable */
	std::shared_ptr<GLCore::VertexArray> __pVao;
	std::shared_ptr<GLCore::ShaderProgram> __pShaderProgram;
	std::shared_ptr<GLCore::Texture2D> __pTexture;
	std::unique_ptr<Poodle::PerspectiveCamera> __pCamera;
	std::array<Poodle::Cube, 20> __cubes;
	
	bool __mouseMoved = false;
	double __mouseXPos = 0.0;
	double __mouseYPos = 0.0;

	bool __wPressed = false;
	bool __sPressed = false;
	bool __aPressed = false;
	bool __dPressed = false;
	bool __qPressed = false;
	bool __ePressed = false;
};