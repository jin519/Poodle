#pragma once

#include <glad/glad.h>
#include "Scene.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Cube.h"
#include <array>
#include <glm/gtc/matrix_transform.hpp>

class TestScene : public Scene 
{
public:
	/* constructor */
	explicit TestScene(GLWindow& window);

	/* member function */
	virtual void onKey(const int key, const int scancode, const int action, const int mods) override;
	virtual void onUpdate(const float deltaTime) override;
	virtual void onRender() override;

private:
	/* member variable */
	std::shared_ptr<VertexArray> __pVao;
	std::shared_ptr<ShaderProgram> __pShaderProgram;
	std::shared_ptr<Texture2D> __pTexture;
	std::array<std::pair<Cube, glm::mat4>, 10> __cubes;
	glm::mat4 __viewMat{ 1.f };
	glm::mat4 __projectionMat{ 1.f };
	std::array<glm::mat4, 10> __modelMat;

	/* member function */
	void __init();
	void __setCubes();
};