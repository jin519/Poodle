#pragma once

#include <glad/glad.h>

namespace GLCore
{
	class VertexAttributeDataStructure
	{
	public:
		/* constructor */
		constexpr VertexAttributeDataStructure(
			const GLint numElements,
			const GLenum elementType,
			const GLboolean normalized = false);

		/* member function */
		constexpr GLsizei memSize() const;

		/* member variable */
		GLint numElements;
		GLenum elementType;
		GLboolean normalized;
	};

	/* constructor */
	constexpr VertexAttributeDataStructure::VertexAttributeDataStructure(
		const GLint numElements,
		const GLenum elementType,
		const GLboolean normalized) :
		numElements(numElements),
		elementType(elementType),
		normalized(normalized)
	{}

	/* member function */
	constexpr GLsizei VertexAttributeDataStructure::memSize() const
	{
		return (sizeof(elementType) * numElements);
	}
}