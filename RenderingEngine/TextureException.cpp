#include "TextureException.h"

/* constructor */
TextureException::TextureException(const std::string& message) noexcept 
	: __message(message) {}

/* member function */
const char* TextureException::what() const noexcept
{
	return __message.c_str();
}