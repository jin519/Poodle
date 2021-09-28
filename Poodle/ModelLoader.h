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

		/// <summary>
		/// 각 aiMesh는 submesh로 간주한다.
		/// 보유하고 있는 vertex attribute 목록을 조사하고, 동일하다면 mesh로 병합한다.
		/// </summary>
		/// <returns>[meshes, pAiMesh2MeshIdxMap]</returns>
		static std::pair<
			std::vector<std::shared_ptr<Mesh>>,
			std::unordered_map<const aiMesh*, int>> __parseMesh(
				const aiScene* const pAiScene,
				const std::unordered_map<GLuint, int>& aiMaterialIdx2MaterialIdxMap);

		class MeshDataset
		{
		public:
			GLuint numIndices{};
			std::vector<GLuint> indexBuffer;

			GLuint numVertices{};
			std::unordered_map<VertexAttributeFlag, std::vector<GLfloat>> attribFlag2VertexBufferMap;

			std::unordered_map<GLuint, size_t> aiMeshIdx2SubmeshInfoIdxMap;
			std::vector<std::unique_ptr<SubmeshInfo>> submeshInfos;
		};
	};
}