#pragma once

#include <glad/glad.h>

namespace Poodle
{
	enum class VertexAttributeFlag : GLuint
	{
		POS3 = 0b0000'0001U,		// position attribute      
		COLOR4 = 0b0000'0010U,		// color attribute  
		NORMAL3 = 0b0000'0100U,		// normal attribute 
		TEXCOORD2 = 0b0000'1000U,	// texture coordinate attribute 
	};

	constexpr VertexAttributeFlag operator|(
		const VertexAttributeFlag lhs,
		const VertexAttributeFlag rhs)
	{
		return VertexAttributeFlag(GLuint(lhs) | GLuint(rhs));
	}

	constexpr VertexAttributeFlag& operator|=(
		VertexAttributeFlag& lhs,
		const VertexAttributeFlag rhs)
	{
		lhs = VertexAttributeFlag(GLuint(lhs) | GLuint(rhs));
		return lhs;
	}

	constexpr bool operator&(
		const VertexAttributeFlag lhs,
		const VertexAttributeFlag rhs)
	{
		return (GLuint(lhs) & GLuint(rhs));
	}
}