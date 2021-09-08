#include "ProgramException.h"

using namespace std; 

namespace GLCore 
{
	ProgramException::ProgramException(const string_view& message) noexcept : 
		exception{ message.data() }
	{}
}