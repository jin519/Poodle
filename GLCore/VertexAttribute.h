#pragma once

#include "VertexAttributeDataStructure.h"
#include <functional>

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

		constexpr bool operator==(const VertexAttribute& rhs) const noexcept;
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

	constexpr bool VertexAttribute::operator==(const VertexAttribute& rhs) const noexcept
	{
		return (
			(location == rhs.location) &&
			(dataStructure == rhs.dataStructure) &&
			(stride == rhs.stride) &&
			(offset == rhs.offset)
		);
	}
}

namespace std
{
	template<>
	class hash<GLCore::VertexAttribute>
	{
	public:
		size_t operator()(GLCore::VertexAttribute const& attrib) const noexcept
		{
			return attrib.location;
		}
	};
}