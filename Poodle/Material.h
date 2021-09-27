#pragma once

#include <glm/glm.hpp>

namespace Poodle
{
	class Material
	{
	public:
		Material() = default;

		constexpr const glm::vec3& getDiffuseColor() const;
		void setDiffuseColor(const glm::vec3& diffuseColor);

		constexpr int getDiffuseTextureIndex() const;
		constexpr void setDiffuseTextureIndex(const int diffuseTextureIndex);

	private:
		glm::vec3 __diffuseColor{ 0.f };
		int __diffuseTextureIndex{ -1 };
	};

	constexpr const glm::vec3& Material::getDiffuseColor() const
	{
		return __diffuseColor; 
	}

	constexpr int Material::getDiffuseTextureIndex() const
	{
		return __diffuseTextureIndex; 
	}

	constexpr void Material::setDiffuseTextureIndex(const int diffuseTextureIndex)
	{
		__diffuseTextureIndex = diffuseTextureIndex; 
	}
}