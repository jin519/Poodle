#include "ShaderProgram.h"
#include "TextReader.h"
#include "ProgramException.h"
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm; 

/* constructor */
ShaderProgram::ShaderProgram(
	const string& vertexShaderPath,
	const string& fragmentShaderPath) 
{
	__init();

	__compile(__vertexShader, vertexShaderPath);
	__compile(__fragmentShader, fragmentShaderPath); 

	__link();
}

/* destructor */
ShaderProgram::~ShaderProgram() 
{
	glDeleteProgram(__id);
}

/* member function */
void ShaderProgram::bind() 
{
	glUseProgram(__id);
}

void ShaderProgram::unbind() 
{
	glUseProgram(0);
}

void ShaderProgram::setUniform1f(const string& variableName, const GLfloat x)
{
	glUseProgram(__id);
	glUniform1f(glGetUniformLocation(__id, variableName.c_str()), x);
}

void ShaderProgram::setUniform2f(const string& variableName, const GLfloat x, const GLfloat y) 
{
	glUseProgram(__id);
	glUniform2f(glGetUniformLocation(__id, variableName.c_str()), x, y);
}

void ShaderProgram::setUniform3f(const string& variableName, const GLfloat x, const GLfloat y, const GLfloat z) 
{
	glUseProgram(__id);
	glUniform3f(glGetUniformLocation(__id, variableName.c_str()), x, y, z);
}

void ShaderProgram::setUniform4f(const string& variableName, const GLfloat x, const GLfloat y, const GLfloat z, const GLfloat w) 
{
	glUseProgram(__id);
	glUniform4f(glGetUniformLocation(__id, variableName.c_str()), x, y, z, w);
}

void ShaderProgram::setUniform1i(const string& variableName, const GLint x) 
{
	glUseProgram(__id);
	glUniform1i(glGetUniformLocation(__id, variableName.c_str()), x);
}

void ShaderProgram::setUniform1ui(const string& variableName, const GLuint x) 
{
	glUseProgram(__id);
	glUniform1ui(glGetUniformLocation(__id, variableName.c_str()), x);
}

void ShaderProgram::setUniformMatrix3f(const string& variableName, const mat3& matrix) 
{
	glUseProgram(__id);
	glUniformMatrix3fv(glGetUniformLocation(__id, variableName.c_str()), 1, false, value_ptr(matrix));
}

void ShaderProgram::setUniformMatrix4f(const string& variableName, const mat4& matrix) 
{
	glUseProgram(__id);
	glUniformMatrix4fv(glGetUniformLocation(__id, variableName.c_str()), 1, false, value_ptr(matrix));
}

void ShaderProgram::__init() 
{
	__id = glCreateProgram();

	if (!__id)
		throw ProgramException("Program generation failed.");

	__vertexShader = glCreateShader(GL_VERTEX_SHADER);
	__fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
}

void ShaderProgram::__compile(GLuint shader, const string& path)
{
	const string& SHADER_SOURCE = TextReader::read(path);
	const char* const RAW_SHADER_SOURCE = SHADER_SOURCE.c_str();

	glShaderSource(shader, 1, &RAW_SHADER_SOURCE, nullptr);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &__success);

	if (!__success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

		throw ProgramException(infoLog);
	}
}

void ShaderProgram::__link() 
{
	glAttachShader(__id, __vertexShader);
	glAttachShader(__id, __fragmentShader);
	glLinkProgram(__id);
	glGetProgramiv(__id, GL_LINK_STATUS, &__success);
	
	if (!__success)
	{
		GLchar infoLog[512];
		glGetProgramInfoLog(__id, sizeof(infoLog), nullptr, infoLog);

		throw ProgramException(infoLog);
	}

	__deleteShader();
}

void ShaderProgram::__deleteShader() 
{
	glDeleteShader(__vertexShader);
	__vertexShader = 0U;

	glDeleteShader(__fragmentShader);
	__fragmentShader = 0U;
}