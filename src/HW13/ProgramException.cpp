#include "ProgramException.h"

/* constructor */
ProgramException::ProgramException(const std::string& message) noexcept : __message(message) {}

/* member function */
const char* ProgramException::what() const noexcept
{
	return __message.c_str();
}