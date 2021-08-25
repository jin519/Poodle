#pragma once

#include <string_view>
#include <exception>

namespace GLCore
{
	class GLWindowException : public std::exception
	{
	public:
		GLWindowException(const std::string_view& message) noexcept;
	};
}