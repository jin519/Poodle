#include <assimp/postprocess.h>
#include "ModelLoader.h"
#include "../GLCore/TextureUtil.h"
#include "VertexAttributeFactory.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	unique_ptr<Model> ModelLoader::load(const string_view& filePath)
	{
		Assimp::Importer importer; 
		const aiScene* const pAiScene = __loadScene(importer, filePath);

		if (!pAiScene || (pAiScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE))
			throw exception{ importer.GetErrorString() };

		if (!pAiScene->HasMeshes())
			return nullptr;

		const filesystem::path& parentDir = filesystem::path{ filePath }.parent_path();
		const auto& aiMaterialIndex2MaterialMap = __parseMaterial(pAiScene, parentDir);

		const auto& [aiMeshIndex2AttribFlagSubMeshInfoIndexPairMap, attribFlag2MeshDatasetMap] = __parseMesh(pAiScene);

		return nullptr; 
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

	unordered_map<GLuint, shared_ptr<Material>> ModelLoader::__parseMaterial(
		const aiScene* const pAiScene,
		const filesystem::path& textureDir)
	{
		unordered_map<GLuint, shared_ptr<Material>> retVal;

		const auto getTexture = [&textureDir](
			const aiMaterial* const pAiMaterial, 
			const aiTextureType textureType) -> pair<Texture2D*, GLfloat>
		{
			Texture2D* pTexture{}; 

			aiString textureName;
			aiTextureMapping mappingCoord{ aiTextureMapping::aiTextureMapping_UV };
			GLuint uvIndex{};
			ai_real blendFactor{ 1.f };
			aiTextureOp operation{ aiTextureOp::aiTextureOp_Add };
			aiTextureMapMode wrapModes[3]
			{
				aiTextureMapMode::aiTextureMapMode_Wrap,
				aiTextureMapMode::aiTextureMapMode_Wrap,
				aiTextureMapMode::aiTextureMapMode_Wrap
			};

			if (pAiMaterial->GetTextureCount(textureType))
			{
				 pAiMaterial->GetTexture(
					textureType, 
					0U, 
					&textureName, 
					&mappingCoord,
					&uvIndex, 
					&blendFactor, 
					&operation, 
					wrapModes);

				const string& imagePath = (textureDir / textureName.C_Str()).generic_string();

				pTexture = TextureUtil::createTexture2DFromImage(imagePath);
			}

			return { pTexture, blendFactor };
		};

		for (GLuint materialIter = 0U; materialIter < pAiScene->mNumMaterials; ++materialIter) 
		{
			const aiMaterial* const pAiMaterial = pAiScene->mMaterials[materialIter];

			const auto& [pDiffuseTexture, diffuseTextureBlendFactor] = getTexture(
				pAiMaterial,
				aiTextureType::aiTextureType_DIFFUSE);

			shared_ptr<Material> pMaterial = make_shared<Material>();
			
			pMaterial->setDiffuseTexture(shared_ptr<Texture2D>{ pDiffuseTexture });
			pMaterial->setDiffuseTextureBlendFactor(diffuseTextureBlendFactor);
			
			retVal.emplace(materialIter, pMaterial);
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
		unordered_map<GLuint, pair<VertexAttributeFlag, size_t>>, 
		unordered_map<VertexAttributeFlag, ModelLoader::MeshDataset>> ModelLoader::__parseMesh(const aiScene* const pAiScene)
	{
		pair<
			unordered_map<GLuint, pair<VertexAttributeFlag, size_t>>,
			unordered_map<VertexAttributeFlag, ModelLoader::MeshDataset>> retVal; 

		auto& aiMeshIndex2AttribFlagSubmeshInfoIndexPairMap = retVal.first;
		auto& attribFlag2MeshDatasetMap = retVal.second; 

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
			
			aiMeshIndex2AttribFlagSubmeshInfoIndexPairMap.emplace(
				meshIter,
				make_pair(attribFlag, meshDataset.submeshInfo.size()));

			meshDataset.submeshInfo.emplace_back(make_unique<SubmeshInfo>(
				numSubmeshIndices, 
				meshDataset.numIndices)); 

			meshDataset.numIndices += numSubmeshIndices; 
			meshDataset.numVertices += numVertices; 
		}

		for (const auto& [aiMeshIndex, attribFlagSubMeshInfoIndexPair] : aiMeshIndex2AttribFlagSubmeshInfoIndexPairMap) 
		{
			const auto& [attribFlag, subMeshInfoIndex] = attribFlagSubMeshInfoIndexPair;
		}

		return retVal;
	}

	

		//for (const auto& [attribFlag, meshIndices] : attribFlag2AiMeshIndiceMap) 
		//{
		//	MeshDataset& meshDataset = attribFlag2MeshDatasetMap[attribFlag]; 
		//	
		//	vector<GLuint>& indexBuffer = meshDataset.indexBuffer;
		//	indexBuffer.reserve(meshDataset.numIndices);
		//	
		//	auto& attrib2VertexBufferMap = meshDataset.attrib2VertexBufferMap;
		//	const size_t numMeshVertices = size_t(meshDataset.numVertices);

		//	vector<GLfloat>& positionBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::POSITION)];
		//	positionBuffer.resize(numMeshVertices * 3ULL);

		//	vector<GLfloat>& normalBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::NORMAL)];
		//	if (attribFlag & VertexAttributeFlag::NORMAL)
		//		normalBuffer.resize(numMeshVertices * 3ULL);

		//	vector<GLfloat>& tangentBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::TANGENT)];
		//	if (attribFlag & VertexAttributeFlag::TANGENT)
		//		tangentBuffer.resize(numMeshVertices * 4ULL);

		//	vector<GLfloat>& texcoordBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::TEXCOORD)];
		//	if (attribFlag & VertexAttributeFlag::TEXCOORD)
		//		texcoordBuffer.resize(numMeshVertices * 2ULL);

		//	vector<GLfloat>& colorBuffer = attrib2VertexBufferMap[VertexAttributeFactory::get(VertexAttributeFlag::COLOR)];
		//	if (attribFlag & VertexAttributeFlag::COLOR)
		//		colorBuffer.resize(numMeshVertices * 4ULL);

		//	GLfloat* pPositionCursor = positionBuffer.data();
		//	GLfloat* pNormalCursor = normalBuffer.data(); 
		//	GLfloat* pTangentCursor = tangentBuffer.data();
		//	GLfloat* pTexcoordCursor = texcoordBuffer.data(); 
		//	GLfloat* pColorCursor = colorBuffer.data(); 

		//	for (const GLuint meshIter : meshIndices) 
		//	{
		//		const aiMesh* const pAiMesh = pAiScene->mMeshes[meshIter];

		//		// -------------- INDEX
		//		{
		//			const GLuint subMeshIndexOffset = aiMeshIndex2SubMeshInfoMap[meshIter].getIndexOffset();

		//			for (GLuint faceIter = 0U; faceIter < pAiMesh->mNumFaces; ++faceIter)
		//			{
		//				const aiFace* const pAiFace = (pAiMesh->mFaces + faceIter);

		//				for (GLuint indexIter = 0U; indexIter < pAiFace->mNumIndices; ++indexIter)
		//					indexBuffer.emplace_back(pAiFace->mIndices[indexIter] + subMeshIndexOffset);
		//			}
		//		}

		//		// -------------- VERTEX

		//		const size_t numSubMeshVertices = pAiMesh->mNumVertices; 

		//		// -------------- VERTEX - POSITION
		//		{
		//			const size_t numSubMeshPositions = (numSubMeshVertices * 3ULL); 
		//			const size_t memSize = (sizeof(GLfloat) * numSubMeshPositions);

		//			memcpy(pPositionCursor, pAiMesh->mVertices, memSize);
		//			pPositionCursor += numSubMeshPositions;
		//		}

		//		// -------------- VERTEX - NORMAL
		//		if (normalBuffer.size()) 
		//		{
		//			const size_t numSubMeshNormals = (numSubMeshVertices * 3ULL); 
		//			const size_t memSize = (sizeof(GLfloat) * numSubMeshNormals);

		//			memcpy(pNormalCursor, pAiMesh->mNormals, memSize);
		//			pNormalCursor += numSubMeshNormals; 
		//		}

		//		// -------------- VERTEX - TANGENT
		//		if (tangentBuffer.size())
		//		{
		//			const size_t numSubMeshTangents = (numSubMeshVertices * 4ULL);
		//			const size_t memSize = (sizeof(GLfloat) * numSubMeshTangents);

		//			memcpy(pTangentCursor, pAiMesh->mTangents, memSize);
		//			pTangentCursor += numSubMeshTangents;
		//		}

		//		// -------------- VERTEX - TEXCOORD
		//		if (texcoordBuffer.size())
		//		{
		//			const size_t numSubMeshTexcoords = (numSubMeshVertices * 2ULL);
		//			const size_t memSize = (sizeof(GLfloat) * numSubMeshTexcoords);

		//			memcpy(pTexcoordCursor, pAiMesh->mTextureCoords[0], memSize);
		//			pTexcoordCursor += numSubMeshTexcoords;
		//		}

		//		// -------------- VERTEX - COLOR
		//		if (colorBuffer.size())
		//		{
		//			const size_t numSubMeshColors = (numSubMeshVertices * 4ULL);
		//			const size_t memSize = (sizeof(GLfloat) * numSubMeshColors);

		//			memcpy(pColorCursor, pAiMesh->mColors[0], memSize);
		//			pColorCursor += numSubMeshColors;
		//		}
		//	}
		//}

		//int x = 20; 
//	}
}