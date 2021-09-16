#pragma once

#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <filesystem>
#include "Model.h"

namespace Poodle 
{
	class ModelLoader
	{
	public:
		ModelLoader() = delete; 

		static std::unique_ptr<Model> load(const std::string_view& filePath); 

	private:
		class MeshDataset 
		{
		public:
			GLuint numIndices{};
			std::vector<GLuint> indexBuffer;

			GLuint numVertices{};
			std::unordered_map<GLCore::VertexAttribute, std::vector<GLfloat>> attrib2VertexBufferMap;

			std::vector<std::unique_ptr<SubmeshInfo>> submeshInfo;
		};

		static const aiScene* __loadScene(
			Assimp::Importer& importer,
			const std::string_view& filePath); 

		static std::unordered_map<GLuint, std::shared_ptr<Material>> __parseMaterial(
			const aiScene* const pAiScene,
			const std::filesystem::path& parentDir);

		static VertexAttributeFlag __getMeshAttribFlag(const aiMesh* const pAiMesh);

		static std::pair<
			std::unordered_map<GLuint, VertexAttributeFlag>,
			std::unordered_map<VertexAttributeFlag, MeshDataset>> __parseMesh(const aiScene* const pAiScene);
	};
}