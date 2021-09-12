#include "VertexArray.h"
#include "VertexArrayException.h"

using namespace std; 

namespace GLCore 
{
	VertexArray::VertexArray(
		unordered_map<VertexAttribute, unique_ptr<VertexBuffer>>&& attrib2VertexBufferMap,
		const GLsizei numVertices) : 
		__attrib2VertexBufferMap{ move(attrib2VertexBufferMap) }, 
		__count{ numVertices }, 
		__pDrawFunc{ &VertexArray::__drawArrays }
	{
		__init(); 
	}

	VertexArray::VertexArray(
		unordered_map<VertexAttribute, unique_ptr<VertexBuffer>>&& attrib2VertexBufferMap,
		unique_ptr<IndexBuffer>&& pIndexBuffer,
		const GLsizei numIndices) :
		__attrib2VertexBufferMap{ move(attrib2VertexBufferMap) },
		__pIndexBuffer{ move(pIndexBuffer) }, 
		__count{ numIndices },
		__pDrawFunc{ &VertexArray::__drawElements }
	{
		__init();
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &__id);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(__id);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::draw()
	{
		bind();
		(this->*__pDrawFunc)();
	}

	void VertexArray::__init() 
	{
		glGenVertexArrays(1, &__id);

		if (!__id)
			throw VertexArrayException{ "vertex array generation failed." };

		__applyAttribute(); 
	}

	void VertexArray::__applyAttribute()
	{
		bind();

		for (const auto& [attrib, pVertexBuffer] : __attrib2VertexBufferMap) 
		{
			pVertexBuffer->bind(); 

			glVertexAttribPointer(
				attrib.location,
				attrib.dataStructure.numElements,
				attrib.dataStructure.elementType,
				attrib.dataStructure.normalized,
				attrib.stride,
				reinterpret_cast<const void*>(size_t(attrib.offset)));

			glEnableVertexAttribArray(attrib.location);
		}

		if (__pIndexBuffer)
			__pIndexBuffer->bind();

		unbind();
	}

	void VertexArray::__drawArrays()
	{
		glDrawArrays(__mode, __first, __count);
	}

	void VertexArray::__drawElements()
	{
		glDrawElements(
			__mode, 
			__count, 
			__pIndexBuffer->getIndexType(), 
			reinterpret_cast<const void*>(__pIndexBuffer->getIndexStride() * __first));
	}
}