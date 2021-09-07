#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string_view>

namespace GLCore
{
	class ShaderProgram
	{
	public:
		ShaderProgram(
			const std::string_view& vertexShaderPath,
			const std::string_view& fragmentShaderPath);

		virtual ~ShaderProgram();

		void bind();
		static void unbind();
		
		void setUniform1f(
			const std::string_view& variableName, 
			const GLfloat x);

		void setUniform2f(
			const std::string_view& variableName, 
			const GLfloat x, 
			const GLfloat y);

		void setUniform3f(
			const std::string_view& variableName, 
			const GLfloat x, 
			const GLfloat y, 
			const GLfloat z);
		
		void setUniform4f(
			const std::string_view& variableName, 
			const GLfloat x, 
			const GLfloat y, 
			const GLfloat z, 
			const GLfloat w);

		void setUniform1i(
			const std::string_view& variableName, 
			const GLint x);

		void setUniform1ui(
			const std::string_view& variableName, 
			const GLuint x);

		void setUniformMatrix3f(
			const std::string_view& variableName, 
			const glm::mat3& matrix);

		void setUniformMatrix4f(
			const std::string_view& variableName, 
			const glm::mat4& matrix);

	private:
		void __init();

		void __compile(
			GLuint shader, 
			const std::string_view& path);

		void __link();
		
		void __deleteShader();

		GLuint __id;
		GLuint __vertexShader;
		GLuint __fragmentShader;
		GLint __success;
	};
}