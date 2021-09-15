#include "TextureUtil.h"
#include <stbi/stb_image.h>
#include <stdexcept>

using namespace std; 

namespace GLCore 
{
	Texture2D* TextureUtil::createTexture2DFromImage(
		const string_view& imagePath, 
		GLuint mipmapLevel, 
		bool autoMipmapCreation)
	{
        Texture2D* pTexture{};

        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        stbi_uc* pImg{};
        {
            pImg = stbi_load(
                imagePath.data(), 
                &width, 
                &height, 
                &channels, 
                0);

            if (!pImg)
                throw exception{ "image loading failed." };
        }

        GLenum format;
        {
            switch (channels)
            {
            case 1:
                format = GL_RED;
                break;

            case 3:
                format = GL_RGB;
                break;

            case 4:
                format = GL_RGBA;
                break;

            default:
                throw runtime_error{ "invalid image format." };
            }
        }

        pTexture = new Texture2D{};
        
        pTexture->memoryAlloc(
            width, 
            height, 
            pImg, 
            format, 
            format,
            GL_UNSIGNED_BYTE, 
            mipmapLevel, 
            autoMipmapCreation);

        stbi_image_free(pImg);
        pImg = nullptr;

        return pTexture;
	}
}