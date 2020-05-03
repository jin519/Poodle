#pragma once

#include <glad/glad.h>

class VertexAttributeDataStructure 
{
public:
	/* constructor */
	constexpr VertexAttributeDataStructure(
		const GLint numElements,
		const GLenum elementType,
		const GLboolean normalized = false) : 
		numElements(numElements),
		elementType(elementType),
		normalized(normalized)
	{}

	/* member function */
	constexpr GLsizei memSize() const 
	{
		return (sizeof(elementType) * numElements);
	}

	/* member variable */
	GLint numElements; 
	GLenum elementType; 
	GLboolean normalized; 
};