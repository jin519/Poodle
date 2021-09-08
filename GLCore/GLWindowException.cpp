#include "GLWindowException.h"

using namespace std; 

namespace GLCore 
{
	GLWindowException::GLWindowException(const string_view& message) noexcept : 
		exception{ message.data() }
	{}
}