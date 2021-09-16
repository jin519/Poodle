#pragma once

#include "Constant.h"

namespace Poodle
{
	enum class VertexAttributeFlag : GLuint
	{
		NONE = 0U, 
		POSITION = (1U << Constant::AttribLocation::position),	// vec3 | float | XYZ vertex positions
		NORMAL = (1U << Constant::AttribLocation::normal),		// vec3 | float | Normalized XYZ vertex normals
		TANGENT = (1U << Constant::AttribLocation::tangent),	// vec3 | float 
		TEXCOORD = (1U << Constant::AttribLocation::texcoord),	// vec2 | float | UV texture coordinates for the first set
		COLOR = (1U << Constant::AttribLocation::color),		// vec4 | float | RGBA vertex color
		JOINTS = (1U << Constant::AttribLocation::joints),		// vec4 | float 
		WEIGHTS = (1U << Constant::AttribLocation::weights)		// vec4 | float
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