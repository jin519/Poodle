#include "VertexArray.h"
#include "VertexArrayException.h"

using namespace std;

namespace GLCore
{
	/* constructor */
	VertexArray::VertexArray(
		const vector<VertexAttribute>& attribList,
		const shared_ptr<VertexBuffer>& pVertexBuffer,
		const GLsizei numVertices) :
		__pVertexBuffer(pVertexBuffer),
		__count(numVertices),
		__pDrawFunc(&VertexArray::__drawArrays)
	{
		__init(attribList);
	}

	VertexArray::VertexArray(
		const vector<VertexAttribute>& attribList,
		const shared_ptr<VertexBuffer>& pVertexBuffer,
		const shared_ptr<IndexBuffer>& pIndexBuffer,
		const GLsizei numIndices) :
		__pVertexBuffer(pVertexBuffer),
		__pIndexBuffer(pIndexBuffer),
		__count(numIndices),
		__pDrawFunc(&VertexArray::__drawElements)
	{
		__init(attribList);
	}

	/* destructor */
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &__id);
	}

	/* static function */
	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	/* member function */
	void VertexArray::bind()
	{
		glBindVertexArray(__id);
	}

	void VertexArray::draw()
	{
		bind();
		(this->*__pDrawFunc)();
	}

	void VertexArray::__init(const vector<VertexAttribute>& attribList)
	{
		glGenVertexArrays(1, &__id);

		if (!__id)
			throw VertexArrayException("Vertex Array Generation failed.");

		__applyAttribute(attribList);
	}

	void VertexArray::__applyAttribute(const vector<VertexAttribute>& attribList)
	{
		bind();

		__pVertexBuffer->bind();

		if (__pIndexBuffer)
			__pIndexBuffer->bind();

		for (const auto& attribute : attribList)
		{
			glVertexAttribPointer(
				attribute.location,
				attribute.dataStructure.numElements,
				attribute.dataStructure.elementType,
				attribute.dataStructure.normalized,
				attribute.stride,
				reinterpret_cast<const void*>(size_t(attribute.offset)));

			glEnableVertexAttribArray(attribute.location);
		}

		unbind();
	}

	void VertexArray::__drawArrays()
	{
		glDrawArrays(__mode, __first, __count);
	}

	void VertexArray::__drawElements()
	{
		glDrawElements(__mode, __count, __pIndexBuffer->getIndexType(), reinterpret_cast<const void*>(__pIndexBuffer->getIndexStride() * __first));
	}
}