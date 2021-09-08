#include "BufferException.h"

using namespace std; 

namespace GLCore 
{
	BufferException::BufferException(const string_view& message) noexcept : 
		exception{ message.data() }
	{}
}