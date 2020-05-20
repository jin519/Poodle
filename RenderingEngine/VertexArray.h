#pragma once

#include <vector>
#include <memory>
#include "VertexAttribute.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace GLCore
{
	class VertexArray
	{
	public:
		/* constructor */
		VertexArray(
			const std::vector<VertexAttribute>& attribList,
			const std::shared_ptr<VertexBuffer>& pVertexBuffer,
			const GLsizei numVertices);
		VertexArray(
			const std::vector<VertexAttribute>& attribList,
			const std::shared_ptr<VertexBuffer>& pVertexBuffer,
			const std::shared_ptr<IndexBuffer>& pIndexBuffer,
			const GLsizei numIndices);

		/* destructor */
		~VertexArray();

		/* static function */
		static void unbind();

		/* member function */
		constexpr void setPrimitiveType(const GLenum primitiveType);
		constexpr void setVertexStartingIndex(const GLint index);
		constexpr void setCount(const GLsizei count);
		void bind();
		void draw();

	private:
		/* member function */
		void __init(const std::vector<VertexAttribute>& attribList);
		void __applyAttribute(const std::vector<VertexAttribute>& attribList);
		void __drawArrays();
		void __drawElements();

		/* member variable */
		GLuint __id;
		const std::shared_ptr<VertexBuffer> __pVertexBuffer;
		const std::shared_ptr<IndexBuffer> __pIndexBuffer;
		GLenum __mode = GL_TRIANGLES;
		GLint __first = 0;
		GLsizei __count;
		void (VertexArray::* const __pDrawFunc)();
	};

	constexpr void VertexArray::setPrimitiveType(const GLenum primitiveType)
	{
		__mode = primitiveType;
	}

	constexpr void VertexArray::setVertexStartingIndex(const GLint index)
	{
		__first = index;
	}

	constexpr void VertexArray::setCount(const GLsizei count)
	{
		__count = count;
	}
}