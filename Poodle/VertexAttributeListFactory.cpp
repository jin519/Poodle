#include "VertexAttributeListFactory.h"
#include "VertexAttributeDataStructureFactory.h"

using namespace std;
using namespace GLCore;
using namespace Poodle::Constant; 

namespace Poodle 
{
	vector<VertexAttribute> VertexAttributeListFactory::get(const VertexAttributeFlag flags)
	{
		vector<VertexAttribute> retVal;

		GLsizei stride = 0;
		GLsizei offset = 0;

		if (flags & VertexAttributeFlag::POSITION)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::position, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::NORMAL)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC3);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::normal, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::TANGENT)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::tangent, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::TEXCOORD)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC2);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::texcoord, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::COLOR) 
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::color, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::JOINTS)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);
			const GLsizei memSize = dataStructure.memSize();

			stride += memSize;
			retVal.emplace_back(AttribLocation::joints, dataStructure, 0, 0);
			offset += memSize;
		}

		if (flags & VertexAttributeFlag::WEIGHTS)
		{
			const VertexAttributeDataStructure& dataStructure = VertexAttributeDataStructureFactory::get(VertexAttributeDataStructureType::VEC4);

			stride += dataStructure.memSize();
			retVal.emplace_back(AttribLocation::weights, dataStructure, 0, 0);
		}

		/*for (auto& attribute : retVal)
			attribute.stride = stride;*/

		return retVal;
	}
}