#pragma once

#include <glad/glad.h>

namespace GLCore
{
	class TextureBase abstract
	{
	public:
		/* constructor */
		explicit TextureBase(const GLenum type);
		TextureBase(const TextureBase& src) = delete;
		TextureBase(TextureBase&& src) noexcept = delete;

		/* destructor */
		virtual ~TextureBase();

		/* static function */
		static void unbind(const GLenum type);

		/* member function */
		TextureBase& operator=(const TextureBase& rhs) = delete;
		TextureBase& operator=(TextureBase&& rhs) = delete;
		void bind();
		void activate(const GLuint index);
		void setParameteri(const GLenum paramName, const GLint paramValue);
		void setParameterfv(const GLenum paramName, const GLfloat* const pParamValues);

	protected:
		/* member variable */
		GLuint _id;

	private:
		/* member variable */
		GLenum __type;
	};
}