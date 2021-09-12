#include "ModelLoaderException.h"

using namespace std; 

namespace Poodle 
{
	ModelLoaderException::ModelLoaderException(const string_view& message) noexcept :
		exception{ message.data() }
	{}
}