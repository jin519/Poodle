#pragma once

#include "VertexAttributeDataStructure.h"

namespace GLCore
{
	class VertexAttribute
	{
	public:
		constexpr VertexAttribute(
			const GLuint location,
			const VertexAttributeDataStructure& dataStructure,
			const GLsizei stride,
			const GLsizei offset);

		GLuint location;
		VertexAttributeDataStructure dataStructure;
		GLsizei stride;
		GLsizei offset;
	};

	constexpr VertexAttribute::VertexAttribute(
		const GLuint location,
		const VertexAttributeDataStructure& dataStructure,
		const GLsizei stride,
		const GLsizei offset) :
		location{ location },
		dataStructure{ dataStructure },
		stride{ stride },
		offset{ offset }
	{}
}