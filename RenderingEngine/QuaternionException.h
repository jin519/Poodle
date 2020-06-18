#pragma once

#include <string>
#include <exception>

namespace Poodle 
{
	class QuaternionException : public std::exception 
	{
	public:
		/* constructor */
		QuaternionException(const std::string& message) noexcept;

		/* member function */
		virtual const char* what() const noexcept override;

	private:
		/* member variable */
		const std::string __message;
	};
}