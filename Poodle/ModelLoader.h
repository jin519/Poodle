#pragma once

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <filesystem>
#include <tuple>
#include "Model.h"

namespace Poodle 
{
	class ModelLoader
	{
	public:
		ModelLoader() = delete; 

		static std::unique_ptr<Model> load(const std::string_view& filePath); 

	private:
		static const aiScene* __loadScene(
			Assimp::Importer& importer,
			const std::string_view& filePath); 

		static std::pair<
			std::vector<std::unique_ptr<Node>>,
			std::unordered_map<const aiNode*, int>> __parseNode(const aiScene* const pAiScene);

		static std::shared_ptr<GLCore::Texture2D> __parseTexture(
			const aiMaterial* const pAiMaterial, 
			const aiTextureType textureType, 
			const std::filesystem::path& parentDir);

		/// <returns>[materials, aiMaterialIndex2MaterialIndexMap, textures]</returns>
		static std::tuple<
			std::vector<std::shared_ptr<Material>>, 
			std::unordered_map<GLuint, int>, 
			std::vector<std::shared_ptr<GLCore::Texture2D>>> __parseMaterial(
				const aiScene* const pAiScene,
				const std::filesystem::path& parentDir);

		static VertexAttributeFlag __getMeshAttribFlag(const aiMesh* const pAiMesh);

		static std::pair<
			std::vector<std::shared_ptr<Mesh>>, 
			std::unordered_map<const aiMesh*, int>> __parseMesh(
				const aiScene* const pAiScene, 
				const std::unordered_map<GLuint, int>& aiMaterialIndex2MaterialIndexMap);
	};
}