#include "BufferBase.h"
#include "BufferException.h"

namespace GLCore 
{
	BufferBase::BufferBase(const GLenum type) : __type{ type }
	{
		glGenBuffers(1, &_id); 

		if (!_id)
			throw BufferException{ "buffer generation failed." };
	}

	BufferBase::~BufferBase()
	{
		glDeleteBuffers(1, &_id);
	}

	void BufferBase::memoryAlloc(
		const void* const pData, 
		const GLsizeiptr size, 
		const GLenum updatePattern)
	{
		bind();
		glBufferData(__type, size, pData, updatePattern);
	}

	void BufferBase::bind()
	{
		glBindBuffer(__type, _id);
	}

	void BufferBase::unbind(const GLenum type)
	{
		glBindBuffer(type, 0);
	}
}