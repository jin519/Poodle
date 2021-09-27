#include "VertexArray.h"
#include <exception>

using namespace std; 

namespace GLCore 
{
	VertexArray::VertexArray(
		unordered_map<VertexAttribute, unique_ptr<VertexBuffer>>&& attrib2VertexBufferMap,
		unique_ptr<IndexBuffer>&& pIndexBuffer,
		const GLsizei numIndices) :
		__attrib2VertexBufferMap{ move(attrib2VertexBufferMap) },
		__pIndexBuffer{ move(pIndexBuffer) }, 
		__count{ numIndices }
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
		draw(__count, __first); 
	}

	void VertexArray::draw(
		const GLsizei count,
		const size_t first) 
	{
		bind();

		glDrawElements(
			__mode,
			count,
			__pIndexBuffer->getIndexType(),
			reinterpret_cast<const void*>(__pIndexBuffer->getIndexStride() * first));
	}

	void VertexArray::__init() 
	{
		glGenVertexArrays(1, &__id);

		if (!__id)
			throw exception{ "vertex array generation failed." };

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

		__pIndexBuffer->bind();

		unbind();
	}
}