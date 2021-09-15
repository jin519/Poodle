#pragma once

#include "Texture2D.h"
#include <string_view>

namespace GLCore 
{
	class TextureUtil 
	{
	public:
		static Texture2D* createTexture2DFromImage(
			const std::string_view& imagePath, 
			GLuint mipmapLevel = 0U, 
			bool autoMipmapCreation = true);
	};
}