#pragma once

#include <string_view>
#include <assimp/Importer.hpp> 
#include <assimp/scene.h>
#include <memory>
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

		static VertexAttributeFlag __getMeshAttribFlag(const aiMesh* const pAiMesh);
		
		static void __parseMesh(const aiScene* const pAiScene); 
	};
}