#include "QuaternionException.h"

using namespace std;

namespace Poodle 
{
	/* constructor */
	QuaternionException::QuaternionException(const string& message) noexcept : __message(message)
	{}

	/* member function */
	const char* QuaternionException::what() const noexcept
	{
		return __message.c_str();
	}
}