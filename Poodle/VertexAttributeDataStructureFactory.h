#pragma once

#include "../GLCore/VertexAttributeDataStructure.h"
#include "VertexAttributeDataStructureType.h"

namespace Poodle
{
	class VertexAttributeDataStructureFactory
	{
	public:
		VertexAttributeDataStructureFactory() = delete; 

		static const GLCore::VertexAttributeDataStructure& get(const VertexAttributeDataStructureType type);
	};
}