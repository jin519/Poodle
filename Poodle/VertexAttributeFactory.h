#pragma once

#include "../GLCore/VertexAttribute.h"
#include "VertexAttributeFlag.h"
#include <unordered_map>

namespace Poodle
{
	class VertexAttributeFactory 
	{
	public:
		VertexAttributeFactory() = delete; 

		static GLCore::VertexAttribute get(const VertexAttributeFlag flag); 
	};
}