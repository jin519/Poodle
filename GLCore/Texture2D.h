#pragma once

#include "TextureBase.h"

namespace GLCore 
{
	class Texture2D : public TextureBase
	{
	public:
		Texture2D(); 
		
		virtual ~Texture2D() = default;

		void memoryAlloc(
			GLsizei width, 
			GLsizei height, 
			const void* const pData,
			GLint internalFormat, 
			GLenum externalFormat,
			GLenum dataType = GL_UNSIGNED_BYTE,
			GLint mipmapLevel = 0,
			bool autoMipmapCreation = true);
	};
}