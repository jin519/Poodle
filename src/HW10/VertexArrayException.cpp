#include "VertexArrayException.h"

using namespace std;

/* constructor */
VertexArrayException::VertexArrayException(const string& message) noexcept
{}

/* member function */
const char* VertexArrayException::what() const noexcept 
{
	return __message.c_str();
}