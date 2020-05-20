#include "BufferBase.h"
#include "BufferException.h"

namespace GLCore
{
	/* constructor */
	BufferBase::BufferBase(const GLenum type) : __type(type)
	{
		glGenBuffers(1, &_id);

		if (!_id)
			throw BufferException("Buffer generation failed.");
	}

	/* destructor */
	BufferBase::~BufferBase()
	{
		glDeleteBuffers(1, &_id);
	}

	/* static function */
	void BufferBase::unbind(const GLenum type)
	{
		glBindBuffer(type, 0);
	}

	/* member function */
	void BufferBase::bind()
	{
		glBindBuffer(__type, _id);
	}

	void BufferBase::memoryAlloc(const void* const pData, const GLsizeiptr size, const GLenum updatePattern)
	{
		bind();
		glBufferData(__type, size, pData, updatePattern);
	}
}