#include "IndexBuffer.h"

/* constructor */
IndexBuffer::IndexBuffer() : 
	BufferBase(GL_ELEMENT_ARRAY_BUFFER)
{}

IndexBuffer::IndexBuffer(
	const void* const pData,
	const GLsizeiptr size,
	const GLenum updatePattern) : 
	BufferBase(GL_ELEMENT_ARRAY_BUFFER)
{
	memoryAlloc(pData, size, updatePattern);
}