#pragma once

#include <glad/glad.h>

namespace Poodle 
{
	class SubMeshInfo 
	{
	public:
		SubMeshInfo() = default; 

		constexpr SubMeshInfo(
			const GLuint numIndices,
			const GLuint indexOffset);

		constexpr GLuint getNumIndices() const; 
		constexpr void setNumIndices(const GLuint numIndices); 

		constexpr GLuint getIndexOffset() const; 
		constexpr void setIndexOffset(const GLuint indexOffset); 

	private:
		GLuint __numIndices{};
		GLuint __indexOffset{};
	};
	
	constexpr SubMeshInfo::SubMeshInfo(
		const GLuint numIndices,
		const GLuint indexOffset) :
		__numIndices{ numIndices }, 
		__indexOffset{ indexOffset }
	{}

	constexpr GLuint SubMeshInfo::getNumIndices() const
	{
		return __numIndices;
	}

	constexpr void SubMeshInfo::setNumIndices(const GLuint numIndices)
	{
		__numIndices = numIndices; 
	}

	constexpr GLuint SubMeshInfo::getIndexOffset() const
	{
		return __indexOffset; 
	}

	constexpr void SubMeshInfo::setIndexOffset(const GLuint indexOffset)
	{
		__indexOffset = indexOffset; 
	}
}