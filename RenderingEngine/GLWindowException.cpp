#include "GLWindowException.h"

using namespace std;

/* constructor */
GLWindowException::GLWindowException(const string& message) noexcept : __message(message)
{}

/* member function */
const char* GLWindowException::what() const noexcept
{
	return __message.c_str();
}