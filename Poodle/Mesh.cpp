#include "Mesh.h"

using namespace std; 

namespace Poodle 
{
	void Mesh::addSubMeshInfo(
		const GLuint numIndices,
		const GLuint indexOffset) 
	{
		__subMeshInfoList.emplace_back(make_unique<SubMeshInfo>(numIndices, indexOffset)); 
	}
}