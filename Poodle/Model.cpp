#include "Model.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	Model::Model(
		const string_view& name,
		const int rootNodeIndex,
		vector<unique_ptr<Node>>&& nodes, 
		vector<shared_ptr<Material>>&& materials,
		vector<shared_ptr<Texture2D>>&& textures,
		vector<shared_ptr<Mesh>>&& meshes) :
		__name{ name }, 
		__rootNodeIndex{ rootNodeIndex }, 
		__nodes{ move(nodes) }, 
		__materials{ move(materials) },
		__textures{ move(textures) },
		__meshes{ move(meshes) }
	{}

	void Model::draw(shared_ptr<ShaderProgram>& pShaderProgram)
	{
		for (size_t meshIter = 0ULL; meshIter < __meshes.size(); ++meshIter) 
		{
			Mesh& mesh = *__meshes[meshIter]; 

			pShaderProgram->setUniformMatrix4f("modelMat", __transform.getModelMatrix());
			pShaderProgram->setUniform1ui("attribFlag", GLuint(mesh.getAttribFlag()));

			for (size_t subIter = 0ULL; subIter < mesh.getNumSubmeshInfos(); ++subIter) 
			{
				const SubmeshInfo& submeshInfo = *mesh.getSubmeshInfo(subIter);
				const int materialIndex = submeshInfo.getMaterialIndex(); 
				
				if (materialIndex >= 0) 
				{
					const Material& material = *__materials[materialIndex]; 

					const int diffuseTexIndex = material.getDiffuseTextureIndex();
					const bool hasDiffuseTex = (diffuseTexIndex >= 0);
					
					if (hasDiffuseTex) 
					{
						Texture2D& diffuseTex = *__textures[diffuseTexIndex];

						diffuseTex.activate(Constant::TexLocation::diffuse);

						pShaderProgram->setUniform1i("hasDiffuseTex", hasDiffuseTex);
						pShaderProgram->setUniform1i("diffuseTex", Constant::TexLocation::diffuse);
					}
				}
				else 
				{
					// TODO
				}

				mesh.draw(subIter); 
			}
		}
	}
}