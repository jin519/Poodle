#pragma once

#include "BufferBase.h"

namespace GLCore 
{
	class VertexBuffer : public BufferBase
	{
	public:
		VertexBuffer();

		VertexBuffer(
			const void* const pData,
			const GLsizeiptr size,
			const GLenum updatePattern);
	};
}