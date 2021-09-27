#pragma once

#include "Material.h"

namespace Poodle 
{
	class SubmeshInfo 
	{
	public:
		constexpr SubmeshInfo(
			const GLuint numIndices,
			const GLuint indexOffset, 
			const int materialIndex);

		constexpr GLuint getNumIndices() const; 
		constexpr GLuint getIndexOffset() const; 

		constexpr int getMaterialIndex() const; 

	private:
		GLuint __numIndices{};
		GLuint __indexOffset{};

		int __materialIndex{ -1 };
	};
	
	constexpr SubmeshInfo::SubmeshInfo(
		const GLuint numIndices,
		const GLuint indexOffset, 
		const int materialIndex) :
		__numIndices{ numIndices }, 
		__indexOffset{ indexOffset }, 
		__materialIndex{ materialIndex }
	{}

	constexpr GLuint SubmeshInfo::getNumIndices() const
	{
		return __numIndices;
	}

	constexpr GLuint SubmeshInfo::getIndexOffset() const
	{
		return __indexOffset; 
	}

	constexpr int SubmeshInfo::getMaterialIndex() const 
	{
		return __materialIndex;
	}
}