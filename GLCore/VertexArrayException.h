#pragma once

#include <string_view>
#include <exception>

namespace GLCore 
{
	class VertexArrayException : public std::exception
	{
	public:
		VertexArrayException(const std::string_view& message) noexcept;
	};
}