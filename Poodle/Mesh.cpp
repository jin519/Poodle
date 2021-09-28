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

	void Mesh::draw(
		const GLsizei count,
		const size_t first)
	{
		__pVao->draw(count, first);
	}
}