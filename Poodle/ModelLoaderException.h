#pragma once

#include <string_view>
#include <exception>

namespace Poodle 
{
	class ModelLoaderException : public std::exception
	{
	public:
		ModelLoaderException(const std::string_view& message) noexcept;
	};
}