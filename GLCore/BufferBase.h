#pragma once

#include <glad/glad.h>

namespace GLCore 
{
	class BufferBase
	{
	public:
		explicit BufferBase(const GLenum type);

		BufferBase(const BufferBase& src) = delete;
		BufferBase(BufferBase&& src) noexcept = delete;

		virtual ~BufferBase();

		void memoryAlloc(
			const void* const pData, 
			const GLsizeiptr size, 
			const GLenum updatePattern);

		void bind();
		static void unbind(const GLenum type);

		BufferBase& operator=(const BufferBase& rhs) = delete;
		BufferBase& operator=(BufferBase&& rhs) noexcept = delete;

	protected:
		GLuint _id;

	private:
		GLenum __type;
	};
}