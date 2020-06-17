#pragma once

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
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

private:
	/* member function */
	void __init();
	void __setCube();

	/* member variable */
	std::shared_ptr<GLCore::VertexArray> __pVao;
	std::shared_ptr<GLCore::ShaderProgram> __pShaderProgram;
	std::shared_ptr<GLCore::Texture2D> __pTexture;
	Poodle::Cube __cube;
	glm::mat4 __viewMat{ 1.f };
	glm::mat4 __projectionMat{ 1.f };

	bool __wFlag = false;
	bool __sFlag = false;
	bool __dFlag = false;
	bool __aFlag = false;
	bool __eFlag = false;
	bool __qFlag = false;
};