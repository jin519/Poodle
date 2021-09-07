#include "VertexAttributeListFactory.h"
#include "VertexAttributeDataStructureFactory.h"

using namespace std;
using namespace GLCore;

namespace Poodle 
{
	vector<VertexAttribute> VertexAttributeListFactory::get(const VertexAttributeFlag flags)
	{
		vector<VertexAttribute> retVal;

		GLuint location = 0;
		GLsizei stride = 0;
		GLsizei offset = 0;

		if (flags & VertexAttributeFlag::POS3)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(location++, dataStructure, 0, offset);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::COLOR4)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(location++, dataStructure, 0, offset);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::NORMAL3)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(location++, dataStructure, 0, offset);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::TEXCOORD2)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC2);

			stride += dataStructure.memSize();
			retVal.emplace_back(location++, dataStructure, 0, offset);
		}

		for (auto& attribute : retVal)
			attribute.stride = stride;

		return retVal;
	}
}