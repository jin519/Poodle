#include <assimp/postprocess.h>
#include <stack>
#include "ModelLoader.h"
#include "VertexAttributeFactory.h"
#include "../GLCore/TextureUtil.h"

using namespace std; 
using namespace glm;
using namespace GLCore; 

namespace Poodle 
{
	unique_ptr<Model> ModelLoader::load(const string_view& filePath)
	{
		unique_ptr<Model> retVal{};

		Assimp::Importer importer; 
		const aiScene* const pAiScene = __loadScene(importer, filePath);

		if (!pAiScene || (pAiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
			throw exception{ importer.GetErrorString() };

		if (!pAiScene->HasMeshes())
			return nullptr;

		const filesystem::path& parentDir = filesystem::path{ filePath }.parent_path();
		auto [materials, aiMaterial2MaterialIndexMap, textures] = __parseMaterial(
			pAiScene, 
			parentDir); 

		auto [nodes, aiNode2NodeIndexMap] = __parseNode(pAiScene);

		auto [meshes, aiMesh2MeshIndexMap] = __parseMesh(
			pAiScene, 
			aiMaterial2MaterialIndexMap);

		retVal = make_unique<Model>(
			pAiScene->mName.C_Str(),
			aiNode2NodeIndexMap.at(pAiScene->mRootNode),
			move(nodes),
			move(materials),
			move(textures),
			move(meshes));

		return retVal; 
	}

	const aiScene* ModelLoader::__loadScene(
		Assimp::Importer& importer, 
		const string_view& filePath)
	{
		return importer.ReadFile(filePath.data(), 
			aiPostProcessSteps::aiProcess_CalcTangentSpace |
			aiPostProcessSteps::aiProcess_JoinIdenticalVertices |
			aiPostProcessSteps::aiProcess_Triangulate |
			aiPostProcessSteps::aiProcess_GenSmoothNormals |
			aiPostProcessSteps::aiProcess_LimitBoneWeights |
			aiPostProcessSteps::aiProcess_ValidateDataStructure |
			aiPostProcessSteps::aiProcess_ImproveCacheLocality |
			aiPostProcessSteps::aiProcess_RemoveRedundantMaterials |
			aiPostProcessSteps::aiProcess_FixInfacingNormals |
			aiPostProcessSteps::aiProcess_SortByPType |
			aiPostProcessSteps::aiProcess_FindDegenerates |
			aiPostProcessSteps::aiProcess_FindInvalidData |
			aiPostProcessSteps::aiProcess_FindInstances |
			aiPostProcessSteps::aiProcess_FlipUVs |
			aiPostProcessSteps::aiProcess_Debone);
	}

	pair<
		vector<unique_ptr<Node>>,
		unordered_map<const aiNode*, int>> ModelLoader::__parseNode(const aiScene* const pAiScene)
	{
		pair<vector<unique_ptr<Node>>, unordered_map<const aiNode*, int>> retVal;
		auto& [nodes, aiNode2NodeIndexMap] = retVal;

		stack<const aiNode*> nodeStack;
		nodeStack.emplace(pAiScene->mRootNode);

		while (nodeStack.size())
		{
			const aiNode* const pAiNode = nodeStack.top();
			nodeStack.pop();

			const int nodeIndex = int(nodes.size());
			aiNode2NodeIndexMap.emplace(pAiNode, nodeIndex);

			const string& name = pAiNode->mName.C_Str();
			const mat4& localJointMatrix = transpose(reinterpret_cast<const mat4&>(pAiNode->mTransformation));
			nodes.emplace_back(make_unique<Node>(name, localJointMatrix));

			const aiNode* const pAiParentNode = pAiNode->mParent;
			if (pAiParentNode)
			{
				const int parentIndex = aiNode2NodeIndexMap.at(pAiParentNode);
				nodes[parentIndex]->addChildIndex(nodeIndex);
			}

			for (GLuint childIter = 0U; childIter < pAiNode->mNumChildren; ++childIter)
				nodeStack.emplace(pAiNode->mChildren[childIter]);
		}

		return retVal;
	}

	shared_ptr<Texture2D> ModelLoader::__parseTexture(
		const aiMaterial* const pAiMaterial, 
		const aiTextureType textureType, 
		const filesystem::path& parentDir)
	{
		shared_ptr<Texture2D> pRetVal{};

		if (pAiMaterial->GetTextureCount(textureType)) 
		{
			aiString path;
			ai_real blendFactor{ 1.f };
			{
				pAiMaterial->GetTexture(
					textureType,
					0U,
					&path,
					nullptr,
					nullptr,
					&blendFactor,
					nullptr,
					nullptr);
			}

			pRetVal = shared_ptr<Texture2D>{ 
				TextureUtil::createTexture2DFromImage(
					(parentDir / path.C_Str()).generic_string()) };
			
			pRetVal->setBlendFactor(blendFactor); 

			pRetVal->setParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
			pRetVal->setParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
			pRetVal->setParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			pRetVal->setParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}

		return pRetVal;
	}

	tuple<
		vector<shared_ptr<Material>>, 
		unordered_map<GLuint, int>, 
		vector<shared_ptr<Texture2D>>> ModelLoader::__parseMaterial(
			const aiScene* const pAiScene, 
			const filesystem::path& parentDir)
	{
		tuple<vector<shared_ptr<Material>>, unordered_map<GLuint, int>, std::vector<std::shared_ptr<GLCore::Texture2D>>> retVal;
		auto& [materials, aiMaterialIndex2MaterialIndexMap, textures] = retVal; 

		for (GLuint materialIter = 0U; materialIter < pAiScene->mNumMaterials; ++materialIter) 
		{
			const aiMaterial* const pAiMaterial = pAiScene->mMaterials[materialIter];

			aiMaterialIndex2MaterialIndexMap.emplace(materialIter, int(materials.size()));

			materials.emplace_back(make_shared<Material>());
			shared_ptr<Material>& pMaterial = materials.back();

			// ----------------------------------- DIFFUSE

			const shared_ptr<Texture2D>& pDiffuseTexture = __parseTexture(
				pAiMaterial,
				aiTextureType::aiTextureType_DIFFUSE,
				parentDir);
			
			if (pDiffuseTexture)
			{
				aiColor3D diffuseColor{ 0.f, 0.f, 0.f };
				pAiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor); 

				pMaterial->setDiffuseTextureIndex(int(textures.size()));
				pMaterial->setDiffuseColor({ diffuseColor.r, diffuseColor.g, diffuseColor.b }); 

				textures.emplace_back(pDiffuseTexture);
			}
		}

		return retVal; 
	}

	VertexAttributeFlag ModelLoader::__getMeshAttribFlag(const aiMesh* const pAiMesh)
	{
		if (!pAiMesh->HasPositions())
			throw exception{ "mesh has no position." };

		VertexAttributeFlag retVal{VertexAttributeFlag::POSITION}; 

		if (pAiMesh->HasNormals())
			retVal |= VertexAttributeFlag::NORMAL; 

		if (pAiMesh->HasTangentsAndBitangents())
			retVal |= VertexAttributeFlag::TANGENT; 

		if (pAiMesh->HasTextureCoords(0U))
			retVal |= VertexAttributeFlag::TEXCOORD; 

		if (pAiMesh->HasVertexColors(0U))
			retVal |= VertexAttributeFlag::COLOR; 

		return retVal;
	}

	pair<
		vector<shared_ptr<Mesh>>, 
		unordered_map<const aiMesh*, int>> ModelLoader::__parseMesh(
			const aiScene* const pAiScene, 
			const unordered_map<GLuint, int>& aiMaterialIndex2MaterialIndexMap)
	{
		pair<vector<shared_ptr<Mesh>>, unordered_map<const aiMesh*, int>> retVal; 
		auto& [meshes, aiMesh2MeshIndexMap] = retVal;

		class MeshDataset
		{
		public:
			GLuint numIndices{};
			std::vector<GLuint> indexBuffer;

			GLuint numVertices{};
			std::unordered_map<GLCore::VertexAttribute, std::vector<GLfloat>> attrib2VertexBufferMap;

			std::vector<std::unique_ptr<SubmeshInfo>> submeshInfo;
		};
		
		unordered_map<GLuint, pair<VertexAttributeFlag, size_t>> aiMeshIndex2AttribFlagSubMeshIndexPairMap; 
		unordered_map<VertexAttributeFlag, MeshDataset> attribFlag2MeshDatasetMap; 
		unordered_map<VertexAttributeFlag, vector<GLuint>> attribFlag2AiMeshIndicesMap; 
		
		/*
			각 aiMesh는 submesh로 간주한다.
			attribute flag가 동일한 submesh는 동일한 mesh에 소속된다.
		*/
		for (GLuint meshIter = 0U; meshIter < pAiScene->mNumMeshes; ++meshIter) 
		{
			const aiMesh* const pAiMesh = pAiScene->mMeshes[meshIter];

			const GLuint numVertices = pAiMesh->mNumVertices;
			if (!numVertices)
				continue;
			
			GLuint numSubmeshIndices{};
			for (GLuint faceIter = 0U; faceIter < pAiMesh->mNumFaces; ++faceIter)
			{
				const aiFace* const pAiFace = (pAiMesh->mFaces + faceIter);
				numSubmeshIndices += pAiFace->mNumIndices;
			}
			
			const VertexAttributeFlag attribFlag = __getMeshAttribFlag(pAiMesh);
			MeshDataset& meshDataset = attribFlag2MeshDatasetMap[attribFlag];

			vector<unique_ptr<SubmeshInfo>>& submeshInfo = meshDataset.submeshInfo; 
			const size_t subMeshIndex = submeshInfo.size();

			aiMeshIndex2AttribFlagSubMeshIndexPairMap.emplace(
				meshIter, 
				make_pair(attribFlag, subMeshIndex)); 
			
			submeshInfo.emplace_back(make_unique<SubmeshInfo>(
				numSubmeshIndices, 
				meshDataset.numIndices)); 
			
			meshDataset.numIndices += numSubmeshIndices; 
			meshDataset.numVertices += numVertices; 

			attribFlag2AiMeshIndicesMap[attribFlag].emplace_back(meshIter);
		}

		for (const auto& [attribFlag, aiMeshIndices] : attribFlag2AiMeshIndicesMap) 
		{
			const int meshIndex = int(meshes.size());

			MeshDataset& meshDataset = attribFlag2MeshDatasetMap[attribFlag]; 

			vector<GLuint>& indexBuffer = meshDataset.indexBuffer;
			indexBuffer.reserve(meshDataset.numIndices);

			const size_t numMeshVertices = size_t(meshDataset.numVertices);
			auto& attrib2VertexBufferMap = meshDataset.attrib2VertexBufferMap;

			vector<GLfloat>& positionBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::POSITION)];
			positionBuffer.resize(numMeshVertices * 3ULL);

			vector<GLfloat>& normalBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::NORMAL)];
			if (attribFlag & VertexAttributeFlag::NORMAL)
				normalBuffer.resize(numMeshVertices * 3ULL);

			vector<GLfloat>& tangentBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::TANGENT)];
			if (attribFlag & VertexAttributeFlag::TANGENT)
				tangentBuffer.resize(numMeshVertices * 3ULL);

			vector<GLfloat>& texcoordBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::TEXCOORD)];
			if (attribFlag & VertexAttributeFlag::TEXCOORD)
				texcoordBuffer.resize(numMeshVertices * 2ULL);

			vector<GLfloat>& colorBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::COLOR)];
			if (attribFlag & VertexAttributeFlag::COLOR)
				colorBuffer.resize(numMeshVertices * 4ULL);

			GLfloat* pPositionCursor = positionBuffer.data();
			GLfloat* pNormalCursor = normalBuffer.data();
			GLfloat* pTangentCursor = tangentBuffer.data();
			GLfloat* pTexcoordCursor = texcoordBuffer.data();
			GLfloat* pColorCursor = colorBuffer.data();

			for (const GLuint aiMeshIndex : aiMeshIndices) 
			{
				const aiMesh* const pAiMesh = pAiScene->mMeshes[aiMeshIndex]; 
				const size_t numSubMeshVertices = pAiMesh->mNumVertices;

				aiMesh2MeshIndexMap.emplace(pAiMesh, meshIndex);

				const size_t submeshIndex = aiMeshIndex2AttribFlagSubMeshIndexPairMap[aiMeshIndex].second;
				SubmeshInfo& submeshInfo = *meshDataset.submeshInfo[submeshIndex];

				const int materialIndex = aiMaterialIndex2MaterialIndexMap.at(pAiMesh->mMaterialIndex); 
				submeshInfo.setMaterialIndex(materialIndex); 

				// ----------------------------------- INDEX

				const GLuint submeshIndexOffset = submeshInfo.getIndexOffset();

				for (GLuint faceIter = 0U; faceIter < pAiMesh->mNumFaces; ++faceIter)
				{
					const aiFace* const pAiFace = (pAiMesh->mFaces + faceIter);

					for (GLuint indexIter = 0U; indexIter < pAiFace->mNumIndices; ++indexIter)
						indexBuffer.emplace_back(pAiFace->mIndices[indexIter] + submeshIndexOffset);
				}

				// ----------------------------------- VERTEX - POSITION
				
				const size_t numSubmeshPositions = (numSubMeshVertices * 3ULL); 
				const size_t memSize = (sizeof(GLfloat) * numSubmeshPositions);

				memcpy(pPositionCursor, pAiMesh->mVertices, memSize);
				pPositionCursor += numSubmeshPositions;

				// ----------------------------------- VERTEX - NORMAL
				
				if (normalBuffer.size()) 
				{
					const size_t numSubmeshNormals = (numSubMeshVertices * 3ULL); 
					const size_t memSize = (sizeof(GLfloat) * numSubmeshNormals);

					memcpy(pNormalCursor, pAiMesh->mNormals, memSize);
					pNormalCursor += numSubmeshNormals; 
				}

				// ----------------------------------- VERTEX - TANGENT
				
				if (tangentBuffer.size())
				{
					const size_t numSubmeshTangents = (numSubMeshVertices * 3ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshTangents);

					memcpy(pTangentCursor, pAiMesh->mTangents, memSize);
					pTangentCursor += numSubmeshTangents;
				}

				// ----------------------------------- VERTEX - TEXCOORD
				
				if (texcoordBuffer.size())
				{
					const size_t numSubmeshTexcoords = (numSubMeshVertices * 2ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshTexcoords);

					memcpy(pTexcoordCursor, pAiMesh->mTextureCoords[0], memSize);
					pTexcoordCursor += numSubmeshTexcoords;
				}

				// ----------------------------------- VERTEX - COLOR
				
				if (colorBuffer.size())
				{
					const size_t numSubmeshColors = (numSubMeshVertices * 4ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshColors);

					memcpy(pColorCursor, pAiMesh->mColors[0], memSize);
					pColorCursor += numSubmeshColors;
				}
			}

			unordered_map<VertexAttribute, unique_ptr<VertexBuffer>> attrib2VboMap;
			for (const auto [attrib, vbo] : meshDataset.attrib2VertexBufferMap)
			{
				attrib2VboMap.emplace(
					attrib, 
					make_unique<VertexBuffer>(
						vbo.data(),
						sizeof(GLfloat) * vbo.size(),
						GL_STATIC_DRAW)); 
			}

			unique_ptr<IndexBuffer> pEbo = make_unique<IndexBuffer>(
				indexBuffer.data(), 
				sizeof(GLuint) * indexBuffer.size(), 
				GL_STATIC_DRAW);

			unique_ptr<VertexArray> pVao = make_unique<VertexArray>(
				move(attrib2VboMap),
				move(pEbo),
				static_cast<GLsizei>(indexBuffer.size())); 

			meshes.emplace_back(make_shared<Mesh>(
				attribFlag,
				move(meshDataset.submeshInfo),
				move(pVao))); 
		}

		return retVal;
	}
}