#pragma once

#include <memory>
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
			std::unique_ptr<IndexBuffer>&& pIndexBuffer,
			const GLsizei numIndices); 

		virtual ~VertexArray();

		void bind();
		static void unbind();

		void draw();
		void draw(
			const GLsizei count, 
			const size_t first); 

		constexpr void setPrimitiveType(const GLenum primitiveType);
		constexpr void setVertexStartingIndex(const GLint index);
		constexpr void setCount(const GLsizei count);

	private:
		void __init(); 
		void __applyAttribute(); 

		GLuint __id;
		GLenum __mode{ GL_TRIANGLES };
		GLsizei __count;
		size_t __first{ 0ULL };

		const std::unordered_map<VertexAttribute, std::unique_ptr<VertexBuffer>> __attrib2VertexBufferMap;
		const std::unique_ptr<IndexBuffer> __pIndexBuffer;
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