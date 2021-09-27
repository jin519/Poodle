#pragma once

#include "Node.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "../GLCore/Texture2D.h"

namespace Poodle 
{
	class Model 
	{
	public:
		Model(
			const std::string_view& name, 
			const int rootNodeIndex,
			std::vector<std::unique_ptr<Node>>&& nodes, 
			std::vector<std::shared_ptr<Material>>&& materials,
			std::vector<std::shared_ptr<GLCore::Texture2D>>&& textures,
			std::vector<std::shared_ptr<Mesh>>&& meshes);

		constexpr const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;

		constexpr const std::shared_ptr<Material>& getMaterial(const int materialIndex) const; 

		constexpr const std::shared_ptr<GLCore::Texture2D>& getTexture(const int textureIndex) const; 

		constexpr Transform& getTransform();
		constexpr const Transform& getTransform() const;

	private:
		std::string __name;

		int __rootNodeIndex{ -1 };

		std::vector<std::unique_ptr<Node>> __nodes;
		std::vector<std::shared_ptr<Material>> __materials; 
		std::vector<std::shared_ptr<GLCore::Texture2D>> __textures;
		std::vector<std::shared_ptr<Mesh>> __meshes; 

		Transform __transform; 
	};

	constexpr const std::vector<std::shared_ptr<Mesh>>& Model::getMeshes() const
	{
		return __meshes;
	}

	constexpr const std::shared_ptr<Material>& Model::getMaterial(const int materialIndex) const
	{
		return __materials.at(materialIndex); 
	}

	constexpr const std::shared_ptr<GLCore::Texture2D>& Model::getTexture(const int textureIndex) const
	{
		return __textures.at(textureIndex); 
	}

	constexpr Transform& Model::getTransform()
	{
		return __transform; 
	}

	constexpr const Transform& Model::getTransform() const 
	{
		return __transform; 
	}
}