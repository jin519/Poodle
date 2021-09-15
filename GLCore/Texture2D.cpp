#include "Texture2D.h"

namespace GLCore
{
	Texture2D::Texture2D() : 
		TextureBase{ GL_TEXTURE_2D }
	{}

	void Texture2D::memoryAlloc(
		GLsizei width, 
		GLsizei height, 
		const void* const pData, 
		GLint internalFormat, 
		GLenum externalFormat, 
		GLenum dataType, 
		GLint mipmapLevel, 
		bool autoMipmapCreation)
	{
		bind(); 

		if (autoMipmapCreation)
		{
			glTexImage2D(
				GL_TEXTURE_2D, 
				0, 
				internalFormat,
				width, 
				height, 
				0, 
				externalFormat, 
				dataType, 
				pData);

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else 
			glTexImage2D(
				GL_TEXTURE_2D, 
				mipmapLevel, 
				internalFormat,
				width, 
				height, 
				0, 
				externalFormat, 
				dataType, 
				pData);
	}
}