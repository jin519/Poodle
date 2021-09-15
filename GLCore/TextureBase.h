#pragma once

#include <glad/glad.h>

namespace GLCore 
{
	class TextureBase 
	{
	public:
		explicit TextureBase(const GLenum type);
		virtual ~TextureBase();

		TextureBase(const TextureBase& src) = delete;
		TextureBase(TextureBase&& src) noexcept = delete;

		void bind();
		static void unbind(const GLenum type);
		
		void activate(const GLuint index);

		void setParameteri(
			const GLenum paramName, 
			const GLint paramValue);

		void setParameterfv(
			const GLenum paramName, 
			const GLfloat* const pParamValues);

		TextureBase& operator=(const TextureBase& rhs) = delete;
		TextureBase& operator=(TextureBase&& rhs) = delete;

	protected:
		GLuint _id;

	private:
		GLenum __type;
	};
}