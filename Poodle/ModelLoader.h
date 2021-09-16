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
			GLuint numVertices{};

			std::vector<GLuint> indexBuffer;
			std::unordered_map<GLCore::VertexAttribute, std::vector<GLfloat>> attrib2VertexBufferMap;
		};

		static const aiScene* __loadScene(
			Assimp::Importer& importer,
			const std::string_view& filePath); 

		static std::unordered_map<GLuint, std::shared_ptr<Material>> __parseMaterial(
			const aiScene* const pAiScene,
			const std::filesystem::path& parentDir);

		static VertexAttributeFlag __getMeshAttribFlag(const aiMesh* const pAiMesh);
		
		static void __parseMesh(const aiScene* const pAiScene); 
	};
}