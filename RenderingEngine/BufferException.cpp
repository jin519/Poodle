#include "BufferException.h"

using namespace std;

namespace GLCore
{
	/* constructor */
	BufferException::BufferException(const string& message) noexcept : __message(message)
	{}

	/* member function */
	const char* BufferException::what() const noexcept
	{
		return __message.c_str();
	}
}