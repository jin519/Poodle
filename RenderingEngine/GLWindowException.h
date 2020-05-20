#pragma once

#include <string>
#include <exception>

namespace GLCore
{
	class GLWindowException : public std::exception
	{
	public:
		/* constructor */
		GLWindowException(const std::string& message) noexcept;

		/* member function */
		virtual const char* what() const noexcept override;

	private:
		/* member variable */
		const std::string __message;
	};
}