#pragma once

#include <string_view>
#include <filesystem>
#include <stdexcept>

namespace GLCore
{
	class ShaderReader
	{
	public:
		ShaderReader() = delete;
		virtual ~ShaderReader() noexcept = default;

		static std::string read(const std::string_view& path);

	private:
		static std::string __preprocess(const std::filesystem::path &srcPath, const bool recursive);
	};
}
