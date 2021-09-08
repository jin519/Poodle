#include "VertexArrayException.h"

using namespace std; 

namespace GLCore 
{
	VertexArrayException::VertexArrayException(const string_view& message) noexcept : 
		exception{ message.data() }
	{}
}