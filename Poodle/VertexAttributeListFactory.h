#pragma once

#include <vector>
#include "../GLCore/VertexAttribute.h"
#include "VertexAttributeFlag.h"

namespace Poodle
{
	class VertexAttributeListFactory
	{
	public:
		VertexAttributeListFactory() = delete; 

		static std::vector<GLCore::VertexAttribute> get(const VertexAttributeFlag flags);
	};
}