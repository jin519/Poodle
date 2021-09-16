#pragma once

#include "../GLCore/Texture2D.h"
#include <memory>

namespace Poodle 
{
	class Material 
	{
	public:
		constexpr const std::shared_ptr<GLCore::Texture2D>& getDiffuseTexture() const;
		void setDiffuseTexture(const std::shared_ptr<GLCore::Texture2D>& pTexture); 

		constexpr GLfloat getDiffuseTextureBlendFactor() const; 
		constexpr void setDiffuseTextureBlendFactor(const GLfloat blendFactor);

	private:
		std::shared_ptr<GLCore::Texture2D> __pDiffuseTexture{};
		GLfloat __diffuseTextureBlendFactor{ 1.f };
	};

	constexpr const std::shared_ptr<GLCore::Texture2D>& Material::getDiffuseTexture() const
	{
		return __pDiffuseTexture;
	}

	constexpr GLfloat Material::getDiffuseTextureBlendFactor() const
	{
		return __diffuseTextureBlendFactor; 
	}

	constexpr void Material::setDiffuseTextureBlendFactor(const GLfloat blendFactor)
	{
		__diffuseTextureBlendFactor = blendFactor; 
	}
}