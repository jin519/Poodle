#pragma once

#include <glad/glad.h>

namespace GLCore
{
	class VertexAttributeDataStructure
	{
	public:
		constexpr VertexAttributeDataStructure(
			const GLint numElements,
			const GLenum elementType,
			const GLboolean normalized = false);

		constexpr GLsizei memSize() const;

		GLint numElements;
		GLenum elementType;
		GLboolean normalized;
	};

	constexpr VertexAttributeDataStructure::VertexAttributeDataStructure(
		const GLint numElements,
		const GLenum elementType,
		const GLboolean normalized) :
		numElements{ numElements },
		elementType{ elementType },
		normalized{ normalized }
	{}

	constexpr GLsizei VertexAttributeDataStructure::memSize() const
	{
		return (sizeof(elementType) * numElements);
	}
}