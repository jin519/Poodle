#pragma once

#include <glad/glad.h>

namespace GLCore
{
	class BufferBase abstract
	{
	public:
		/* constructor */
		explicit BufferBase(const GLenum type);
		BufferBase(const BufferBase& src) = delete;
		BufferBase(BufferBase&& src) noexcept = delete;

		/* destructor */
		virtual ~BufferBase();

		/* static function */
		static void unbind(const GLenum type);

		/* member function */
		BufferBase& operator=(const BufferBase& rhs) = delete;
		BufferBase& operator=(BufferBase&& rhs) noexcept = delete;
		void bind();
		void memoryAlloc(const void* const pData, const GLsizeiptr size, const GLenum updatePattern);

	protected:
		/* member variable */
		GLuint _id;

	private:
		/* member variable */
		GLenum __type;
	};
}