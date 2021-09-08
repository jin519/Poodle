#pragma once

#include "BufferBase.h"

namespace GLCore 
{
	class IndexBuffer : public BufferBase
	{
	public:
		explicit IndexBuffer(const GLenum indexType = GL_UNSIGNED_INT);
		
		IndexBuffer(
			const void* const pData,
			const GLsizeiptr size,
			const GLenum updatePattern,
			const GLenum indexType = GL_UNSIGNED_INT);

		constexpr GLenum getIndexType() const;
		constexpr size_t getIndexStride() const;

	private:
		void __calcIndexStride();

		GLenum __indexType;
		size_t __indexStride = sizeof(GLuint);
	};

	constexpr GLenum IndexBuffer::getIndexType() const
	{
		return __indexType;
	}

	constexpr size_t IndexBuffer::getIndexStride() const
	{
		return __indexStride;
	}
}