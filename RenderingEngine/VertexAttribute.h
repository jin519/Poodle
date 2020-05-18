#pragma once

#include "VertexAttributeDataStructure.h"

class VertexAttribute 
{
public:
	/* constructor */
	constexpr VertexAttribute(
		const GLuint location,
		const VertexAttributeDataStructure& dataStructure,
		const GLsizei stride,
		const GLsizei offset);

	/* member variable */
	GLuint location;
	VertexAttributeDataStructure dataStructure;
	GLsizei stride;
	GLsizei offset;
};

/* constructor */
constexpr VertexAttribute::VertexAttribute(
	const GLuint location,
	const VertexAttributeDataStructure& dataStructure,
	const GLsizei stride,
	const GLsizei offset) :
	location(location),
	dataStructure(dataStructure),
	stride(stride),
	offset(offset)
{}