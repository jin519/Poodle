#pragma once

#include <vector>
#include "VertexAttribute.h"
#include "VertexAttributeFlag.h"

class VertexAttributeListFactory abstract final
{
public:
	/* static function */
	static std::vector<VertexAttribute> get(const VertexAttributeFlag flags);
};