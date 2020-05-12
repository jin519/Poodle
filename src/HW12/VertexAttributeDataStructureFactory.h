#pragma once

#include "VertexAttributeDataStructure.h"
#include "VertexAttributeDataStructureType.h"

class VertexAttributeDataStructureFactory abstract final
{
public:
	/* static function */
	static const VertexAttributeDataStructure& get(
		const VertexAttributeDataStructureType type);
};