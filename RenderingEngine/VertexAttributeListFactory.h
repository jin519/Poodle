#pragma once

#include <vector>
#include "VertexAttribute.h"
#include "VertexAttributeFlag.h"

namespace Poodle
{
	class VertexAttributeListFactory abstract final
	{
	public:
		/* static function */
		static std::vector<GLCore::VertexAttribute> get(const VertexAttributeFlag flags);
	};
}