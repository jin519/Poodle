#include "VertexAttributeListFactory.h"
#include "VertexAttributeDataStructureFactory.h"
#include <utility>

using namespace std;

/* static function */
vector<VertexAttribute> VertexAttributeListFactory::get(const VertexAttributeFlag flags)
{
	vector<VertexAttribute> retVal;
	GLuint location = 0;
	GLsizei stride = 0; 
	GLsizei offset = 0;

	if (flags & VertexAttributeFlag::POS3)
	{
		const VertexAttributeDataStructure& DATA_STRUCTURE = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
		const GLsizei MEM_SIZE = DATA_STRUCTURE.memSize();

		stride += MEM_SIZE;
		retVal.emplace_back(VertexAttribute{ location++, DATA_STRUCTURE, 0, 0 });
		offset += MEM_SIZE;
	}
	
	if (flags & VertexAttributeFlag::COLOR4)
	{
		const VertexAttributeDataStructure& DATA_STRUCTURE = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);
		const GLsizei MEM_SIZE = DATA_STRUCTURE.memSize();

		stride += MEM_SIZE;
		retVal.emplace_back(VertexAttribute{ location++, DATA_STRUCTURE, 0, offset });
		offset += MEM_SIZE;
	}

	if (flags & VertexAttributeFlag::NORMAL3)
	{
		const VertexAttributeDataStructure& DATA_STRUCTURE = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
		const GLsizei MEM_SIZE = DATA_STRUCTURE.memSize();

		stride += MEM_SIZE;
		retVal.emplace_back(VertexAttribute{ location++, DATA_STRUCTURE, 0, offset });
		offset += MEM_SIZE;
	}

	if (flags & VertexAttributeFlag::TEXCOORD2)
	{
		const VertexAttributeDataStructure& DATA_STRUCTURE = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC2);

		stride += DATA_STRUCTURE.memSize();
		retVal.emplace_back(VertexAttribute{ location++, DATA_STRUCTURE, stride, offset });
	}

	for (auto& attribute : retVal) 
		attribute.stride = stride; 

	return retVal;
}
