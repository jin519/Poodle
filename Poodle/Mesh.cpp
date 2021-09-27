#include "Mesh.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	void Mesh::addSubmeshInfo(unique_ptr<SubmeshInfo>&& pSubmeshInfo)
	{
		__submeshInfoList.emplace_back(move(pSubmeshInfo)); 
	}

	void Mesh::setVao(unique_ptr<VertexArray>&& pVao)
	{
		__pVao = move(pVao); 
	}

	Mesh::Mesh(
		const VertexAttributeFlag attribFlag,
		vector<unique_ptr<SubmeshInfo>>&& submeshInfo,
		unique_ptr<VertexArray>&& pVao) :
		__attribFlag{ attribFlag }, 
		__submeshInfoList{ move(submeshInfo) },
		__pVao{ move(pVao) }
	{}

	const SubmeshInfo* Mesh::getSubmeshInfo(const size_t submeshIndex) const
	{
		return __submeshInfoList.at(submeshIndex).get();
	}

	void Mesh::draw(
		const GLsizei count,
		const size_t first)
	{
		__pVao->draw(count, first);
	}
}