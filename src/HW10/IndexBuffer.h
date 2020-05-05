#pragma once

#include "BufferBase.h"

class IndexBuffer : public BufferBase 
{
public:
	/* constructor */
	IndexBuffer();
	IndexBuffer(
		const void* const pData,
		const GLsizeiptr size,
		const GLenum updatePattern);
};