#include "VertexBuffer.h"

/* constructor */
VertexBuffer::VertexBuffer() : 
	BufferBase(GL_ARRAY_BUFFER)
{}

VertexBuffer::VertexBuffer(
	const void* const pData,
	const GLsizeiptr size,
	const GLenum updatePattern) :
	BufferBase(GL_ARRAY_BUFFER)
{
	memoryAlloc(pData, size, updatePattern);
}