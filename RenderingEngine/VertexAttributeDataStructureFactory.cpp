#include "VertexAttributeDataStructureFactory.h"

using namespace GLCore;

namespace Poodle
{
	/* static function */
	const VertexAttributeDataStructure& VertexAttributeDataStructureFactory::get(
		const VertexAttributeDataStructureType type)
	{
		static const VertexAttributeDataStructure VEC2(2, GL_FLOAT);
		static const VertexAttributeDataStructure VEC3(3, GL_FLOAT);
		static const VertexAttributeDataStructure VEC4(4, GL_FLOAT);

		switch (type)
		{
		case VertexAttributeDataStructureType::VEC2:
			return VEC2;

		case VertexAttributeDataStructureType::VEC3:
			return VEC3;

		case VertexAttributeDataStructureType::VEC4:
			return VEC4;
		}

		return VEC2;
	}
}