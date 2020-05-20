#include "TextureUtil.h"
#include "TextureException.h"

using namespace std;

namespace GLCore
{
    /* static function */
    shared_ptr<Texture2D> TextureUtil::createTexture2DFromImage(
        const string& imagePath, GLint mipmapLevel, bool autoMipmapCreation)
    {
        stbi_set_flip_vertically_on_load(true);

        int width, height, channels;
        stbi_uc* pImg = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);

        if (!pImg)
            throw TextureException("Image loading failed.");

        shared_ptr<Texture2D> retVal = make_shared<Texture2D>();

        GLenum format;
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
        }

        retVal->memoryAlloc(
            width, height, pImg, format, format,
            GL_UNSIGNED_BYTE, mipmapLevel, autoMipmapCreation);

        stbi_image_free(pImg);
        pImg = nullptr;

        return retVal;
    }
}