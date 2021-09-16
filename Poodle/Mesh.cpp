#include "Mesh.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	Mesh::Mesh(
		const VertexAttributeFlag attribFlag,
		vector<unique_ptr<SubmeshInfo>>&& submeshInfo,
		unique_ptr<VertexArray>&& pVao) :
		__attribFlag{ attribFlag }, 
		__submeshInfo{ move(submeshInfo) },
		__pVao{ move(pVao) }
	{}

	const SubmeshInfo* Mesh::getSubmeshInfo(const size_t submeshIndex) const
	{
		return __submeshInfo.at(submeshIndex).get();
	}

	const VertexArray* Mesh::getVao() const
	{
		return __pVao.get();
	}
}