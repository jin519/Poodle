#pragma once

#include "VertexAttributeDataStructure.h"
#include "VertexAttributeDataStructureType.h"

namespace Poodle
{
	class VertexAttributeDataStructureFactory abstract final
	{
	public:
		/* static function */
		static const GLCore::VertexAttributeDataStructure& get(const VertexAttributeDataStructureType type);
	};
}