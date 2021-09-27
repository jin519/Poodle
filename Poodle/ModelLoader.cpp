#include <assimp/postprocess.h>
#include <stack>
#include <algorithm>
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
			aiPostProcessSteps::aiProcess_PreTransformVertices | // TEST
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

	unordered_map<VertexAttributeFlag, ModelLoader::MeshDataset> ModelLoader::__parseMeshDataset(
		const aiScene* const pAiScene, 
		const unordered_map<GLuint, int>& aiMaterialIdx2MaterialIdxMap)
	{
		unordered_map<VertexAttributeFlag, MeshDataset> retVal; 

		for (GLuint subIter = 0U; subIter < pAiScene->mNumMeshes; ++subIter)
		{
			const aiMesh* const pAiMesh = pAiScene->mMeshes[subIter];

			const GLuint numVertices = pAiMesh->mNumVertices;
			if (!numVertices)
				continue;

			const VertexAttributeFlag attribFlag = __getMeshAttribFlag(pAiMesh);
			MeshDataset& meshDataset = retVal[attribFlag];

			GLuint numIndices{};
			for (GLuint faceIter = 0U; faceIter < pAiMesh->mNumFaces; ++faceIter)
			{
				const aiFace* const pAiFace = (pAiMesh->mFaces + faceIter);
				numIndices += pAiFace->mNumIndices;
			}

			const int materialIndex = aiMaterialIdx2MaterialIdxMap.at(pAiMesh->mMaterialIndex);

			meshDataset.aiMeshIdx2SubmeshInfoMap.emplace(
				subIter,
				make_unique<SubmeshInfo>(
					numIndices,
					meshDataset.numVertices,
					materialIndex));

			meshDataset.numIndices += numIndices;
			meshDataset.numVertices += numVertices;
		}

		return retVal;
	}

	pair<
		vector<shared_ptr<Mesh>>, 
		unordered_map<const aiMesh*, int>> ModelLoader::__parseMesh(
			const aiScene* const pAiScene, 
			const unordered_map<GLuint, int>& aiMaterialIdx2MaterialIdxMap)
	{
		pair<vector<shared_ptr<Mesh>>, unordered_map<const aiMesh*, int>> retVal; 
		auto& [meshes, pAiMesh2MeshIdxMap] = retVal;

		unordered_map<VertexAttributeFlag, MeshDataset> attribFlag2MeshDatasetMap = __parseMeshDataset(
			pAiScene,
			aiMaterialIdx2MaterialIdxMap); 

		for (auto& [attribFlag, meshDataset] : attribFlag2MeshDatasetMap)
		{
			const int meshIndex = int(meshes.size()); 

			meshes.emplace_back(make_shared<Mesh>(attribFlag));
			Mesh& mesh = *meshes.back(); 

			const size_t numIndices = size_t(meshDataset.numIndices); 
			vector<GLuint>& indexBuffer = meshDataset.indexBuffer;
			const size_t numVertices = size_t(meshDataset.numVertices);
			auto& attribFlag2VertexBufferMap = meshDataset.attribFlag2VertexBufferMap;
			auto& aiMeshIdx2SubmeshInfoMap = meshDataset.aiMeshIdx2SubmeshInfoMap;

			indexBuffer.reserve(numIndices);

			vector<GLfloat>& positionBuffer = attribFlag2VertexBufferMap[VertexAttributeFlag::POSITION];
			vector<GLfloat>& normalBuffer = attribFlag2VertexBufferMap[VertexAttributeFlag::NORMAL];
			vector<GLfloat>& tangentBuffer = attribFlag2VertexBufferMap[VertexAttributeFlag::TANGENT];
			vector<GLfloat>& texcoordBuffer = attribFlag2VertexBufferMap[VertexAttributeFlag::TEXCOORD];
			vector<GLfloat>& colorBuffer = attribFlag2VertexBufferMap[VertexAttributeFlag::COLOR];
			
			positionBuffer.resize(numVertices * 3ULL); 

			if (attribFlag & VertexAttributeFlag::NORMAL)
				normalBuffer.resize(numVertices * 3ULL);

			if (attribFlag & VertexAttributeFlag::TANGENT)
				tangentBuffer.resize(numVertices * 3ULL);

			if (attribFlag & VertexAttributeFlag::TEXCOORD)
				texcoordBuffer.resize(numVertices * 2ULL);

			if (attribFlag & VertexAttributeFlag::COLOR)
				colorBuffer.resize(numVertices * 4ULL);

			GLfloat* pPositionCursor = positionBuffer.data();
			GLfloat* pNormalCursor = normalBuffer.data();
			GLfloat* pTangentCursor = tangentBuffer.data();
			GLfloat* pTexcoordCursor = texcoordBuffer.data();
			GLfloat* pColorCursor = colorBuffer.data();

			/*
				mesh dataset 내 indexBuffer, attribFlag2VertexBufferMap을 채운다.
				mesh 내 submeshInfoList를 채운다.
			*/
			for (auto& [aiMeshIndex, pSubmeshInfo] : aiMeshIdx2SubmeshInfoMap)
			{
				const aiMesh* const pAiMesh = pAiScene->mMeshes[aiMeshIndex]; 

				// ----------------------------------- INDEX

				const GLuint submeshIndexOffset = pSubmeshInfo->getIndexOffset();

				for (GLuint faceIter = 0U; faceIter < pAiMesh->mNumFaces; ++faceIter)
				{
					const aiFace* const pAiFace = (pAiMesh->mFaces + faceIter);

					for (GLuint indexIter = 0U; indexIter < pAiFace->mNumIndices; ++indexIter)
						indexBuffer.emplace_back(pAiFace->mIndices[indexIter] + submeshIndexOffset);
				}

				// ----------------------------------- VERTEX

				const size_t numSubmeshVertices = size_t(pAiMesh->mNumVertices); 

				// ----------------------------------- VERTEX - POSITION

				{
					const size_t numSubmeshPositions = (numSubmeshVertices * 3ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshPositions);

					memcpy(pPositionCursor, pAiMesh->mVertices, memSize);
					pPositionCursor += numSubmeshPositions;
				}

				// ----------------------------------- VERTEX - NORMAL
				
				if (normalBuffer.size()) 
				{
					const size_t numSubmeshNormals = (numSubmeshVertices * 3ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshNormals);

					memcpy(pNormalCursor, pAiMesh->mNormals, memSize);
					pNormalCursor += numSubmeshNormals; 
				}

				// ----------------------------------- VERTEX - TANGENT

				if (tangentBuffer.size())
				{
					const size_t numSubmeshTangents = (numSubmeshVertices * 3ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshTangents);

					memcpy(pTangentCursor, pAiMesh->mTangents, memSize);
					pTangentCursor += numSubmeshTangents;
				}

				// ----------------------------------- VERTEX - TEXCOORD
				
				if (texcoordBuffer.size())
				{
					const size_t numSubmeshTexcoords = (numSubmeshVertices * 2ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshTexcoords);

					memcpy(pTexcoordCursor, pAiMesh->mTextureCoords[0], memSize);
					pTexcoordCursor += numSubmeshTexcoords;
				}

				// ----------------------------------- VERTEX - COLOR
				
				if (colorBuffer.size())
				{
					const size_t numSubmeshColors = (numSubmeshVertices * 4ULL);
					const size_t memSize = (sizeof(GLfloat) * numSubmeshColors);

					memcpy(pColorCursor, pAiMesh->mColors[0], memSize);
					pColorCursor += numSubmeshColors;
				}

				mesh.addSubmeshInfo(move(pSubmeshInfo)); 
				pAiMesh2MeshIdxMap.emplace(pAiMesh, meshIndex); 
			}

			/*
				mesh dataset 정보를 이용하여 mesh 내 vao를 채운다.
			*/
			unique_ptr<VertexArray> pVao{};
			{
				unordered_map<VertexAttribute, unique_ptr<VertexBuffer>> attrib2VboMap;
				unique_ptr<IndexBuffer> pEbo{};

				for (const auto& [attribFlag, vertexBuffer] : attribFlag2VertexBufferMap)
				{
					const size_t numVertices = vertexBuffer.size();
					if (numVertices)
					{
						const VertexAttribute& attrib = VertexAttributeFactory::get(attribFlag);

						unique_ptr<VertexBuffer> pVbo = make_unique<VertexBuffer>(
							vertexBuffer.data(),
							(sizeof(GLfloat) * numVertices),
							GL_STATIC_DRAW);

						attrib2VboMap.emplace(attrib, move(pVbo));
					}
				}

				pEbo = make_unique<IndexBuffer>(
					indexBuffer.data(),
					(sizeof(GLuint) * numIndices),
					GL_STATIC_DRAW);

				pVao = make_unique<VertexArray>(
					move(attrib2VboMap),
					move(pEbo),
					GLsizei(numIndices));

				mesh.setVao(move(pVao));
			}
		}

		return retVal;
	}
}