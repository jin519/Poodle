#pragma once

#include <memory>
#include <string>
#include <glad/glad.h>
#include "stb_image.h"
#include "Texture2D.h"

class TextureUtil abstract final
{
public:
	/* static function */
	static std::shared_ptr<Texture2D> createTexture2DFromImage(
		const std::string& imagePath,
		GLint mipmapLevel = 0,
		bool autoMipmapCreation = true);
};