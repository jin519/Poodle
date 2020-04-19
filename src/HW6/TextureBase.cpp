#include "TextureBase.h"
#include "TextureException.h"

/* constructor */
TextureBase::TextureBase(const GLenum type) : __type(type)
{
	glGenTextures(1, &_id);

	if (!_id)
		throw TextureException("Texture generation failed.");
}

/* destructor */
TextureBase::~TextureBase() 
{
	glDeleteTextures(1, &_id);
}

/* member function */
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
	glActiveTexture(index);
}

void TextureBase::setParameteri(const GLenum paramName, const GLint paramValue) 
{
	glTexParameteri(__type, paramName, paramValue);
}

void TextureBase::setParameterfv(const GLenum paramName, const GLfloat* const pParamValues) 
{
	glTexParameterfv(__type, paramName, pParamValues);
}