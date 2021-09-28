#include "Mesh.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	const SubmeshInfo* Mesh::getSubmeshInfo(const size_t submeshInfoIndex) const
	{
		return __submeshInfos[submeshInfoIndex].get();
	}

	void Mesh::setSubmeshInfos(vector<unique_ptr<SubmeshInfo>>&& submeshInfos)
	{
		__submeshInfos = move(submeshInfos); 
	}

	void Mesh::setVao(unique_ptr<VertexArray>&& pVao)
	{
		__pVao = move(pVao);
	}

	void Mesh::draw(const size_t submeshIndex)
	{
		const SubmeshInfo& submeshInfo = *__submeshInfos[submeshIndex];

		const GLsizei count = GLsizei(submeshInfo.getNumIndices()); 
		const size_t first = size_t(submeshInfo.getFirstIndex()); 

		__pVao->draw(count, first); 
	}
}