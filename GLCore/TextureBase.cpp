#include "TextureBase.h"
#include <exception>

using namespace std; 

namespace GLCore 
{
	TextureBase::TextureBase(const GLenum type) : 
		__type{ type }
	{
		glGenTextures(1, &_id);

		if (!_id)
			throw exception{ "texture generation failed." };
	}

	TextureBase::~TextureBase()
	{
		glDeleteTextures(1, &_id);
	}

	void TextureBase::bind()
	{
		glBindTexture(__type, _id);
	}

	void TextureBase::unbind(const GLenum type)
	{
		glBindTexture(type, 0);
	}

	void TextureBase::activate(const GLuint index)
	{
		glActiveTexture((GL_TEXTURE0 + index));
		bind();
	}

	void TextureBase::setParameteri(
		const GLenum paramName, 
		const GLint paramValue)
	{
		bind();
		glTexParameteri(__type, paramName, paramValue);
	}

	void TextureBase::setParameterfv(
		const GLenum paramName, 
		const GLfloat* const pParamValues)
	{
		bind();
		glTexParameterfv(__type, paramName, pParamValues);
	}
}