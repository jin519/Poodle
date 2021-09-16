#include "VertexAttributeDataStructureFactory.h"
#include <exception>

using namespace std; 
using namespace GLCore;

namespace Poodle 
{
	const VertexAttributeDataStructure& VertexAttributeDataStructureFactory::get(
		const VertexAttributeDataStructureType type)
	{
		static const VertexAttributeDataStructure vec2(2, GL_FLOAT);
		static const VertexAttributeDataStructure vec3(3, GL_FLOAT);
		static const VertexAttributeDataStructure vec4(4, GL_FLOAT);

		switch (type)
		{
		case VertexAttributeDataStructureType::VEC2:
			return vec2;

		case VertexAttributeDataStructureType::VEC3:
			return vec3;

		case VertexAttributeDataStructureType::VEC4:
			return vec4;

		default:
			throw exception{ "invalid vertex attribute data structure type." }; 
		}
	}
}