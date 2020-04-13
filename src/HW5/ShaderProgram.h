#pragma once

#include <string>
#include <glad/glad.h>

class ShaderProgram 
{
public:
	/* constructor */
	ShaderProgram(
		const std::string& vertexShaderPath, 
		const std::string& fragmentShaderPath);

	/* destructor */
	virtual ~ShaderProgram();

	/* member function */
	static void unbind();
	void bind(); 
	void setUniform1f(const std::string& variableName, const GLfloat x);
	void setUniform2f(const std::string& variableName, const GLfloat x, const GLfloat y);
	void setUniform3f(const std::string& variableName, const GLfloat x, const GLfloat y, const GLfloat z);
	void setUniform4f(const std::string& variableName, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w);
	void setUniform1i(const std::string& variableName, const GLint x);
	void setUniform1ui(const std::string& variableName, const GLuint x);

private:
	/* member function */
	void __init();
	void __compile(GLuint shader, const std::string& path);
	void __link();
	void __deleteShader();

	/* member variable */
	GLuint __id;
	GLuint __vertexShader;
	GLuint __fragmentShader;
	GLint __success;
};