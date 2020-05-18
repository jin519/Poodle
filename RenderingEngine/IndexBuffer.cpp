#include "IndexBuffer.h"

/* constructor */
IndexBuffer::IndexBuffer(const GLenum indexType) :
	BufferBase(GL_ELEMENT_ARRAY_BUFFER), 
	__indexType(indexType)
{
	__calcIndexStride();
}

IndexBuffer::IndexBuffer(
	const void* const pData,
	const GLsizeiptr size,
	const GLenum updatePattern, 
	const GLenum indexType) :
	BufferBase(GL_ELEMENT_ARRAY_BUFFER), 
	__indexType(indexType)
{
	__calcIndexStride();
	memoryAlloc(pData, size, updatePattern);
}

/* member function */
void IndexBuffer::__calcIndexStride()
{
	switch (__indexType)
	{
	case GL_UNSIGNED_INT:
		__indexStride = sizeof(GLuint);
		break;
	case GL_UNSIGNED_SHORT:
		__indexStride = sizeof(GLushort);
	}
}