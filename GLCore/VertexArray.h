#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "VertexAttribute.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace GLCore
{
	class VertexArray
	{
	public:
		VertexArray(
			std::unordered_map<VertexAttribute, std::unique_ptr<VertexBuffer>>&& attrib2VertexBufferMap,
			const GLsizei numVertices); 

		VertexArray(
			std::unordered_map<VertexAttribute, std::unique_ptr<VertexBuffer>>&& attrib2VertexBufferMap,
			std::unique_ptr<IndexBuffer>&& pIndexBuffer,
			const GLsizei numIndices); 

		virtual ~VertexArray();

		void bind();
		static void unbind();

		void draw();

		constexpr void setPrimitiveType(const GLenum primitiveType);
		constexpr void setVertexStartingIndex(const GLint index);
		constexpr void setCount(const GLsizei count);

	private:
		void __init(); 
		void __applyAttribute(); 

		void __drawArrays();
		void __drawElements();

		GLuint __id;
		GLenum __mode = GL_TRIANGLES;
		GLint __first = 0;
		GLsizei __count;

		const std::unordered_map<VertexAttribute, std::unique_ptr<VertexBuffer>> __attrib2VertexBufferMap;
		const std::unique_ptr<IndexBuffer> __pIndexBuffer; 

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