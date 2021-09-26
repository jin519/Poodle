#pragma once

#include <string>
#include "Node.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

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
			std::vector<std::shared_ptr<Mesh>>&& meshes);

		constexpr const std::vector<std::shared_ptr<Material>>& getMaterials() const; 

		constexpr const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;

		constexpr Transform& getTransform();
		constexpr const Transform& getTransform() const;

	private:
		std::string __name;

		int __rootNodeIndex{ -1 };

		std::vector<std::unique_ptr<Node>> __nodes;
		std::vector<std::shared_ptr<Material>> __materials; 
		std::vector<std::shared_ptr<Mesh>> __meshes; 

		Transform __transform; 
	};

	constexpr const std::vector<std::shared_ptr<Material>>& Model::getMaterials() const
	{
		return __materials; 
	}

	constexpr const std::vector<std::shared_ptr<Mesh>>& Model::getMeshes() const
	{
		return __meshes;
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