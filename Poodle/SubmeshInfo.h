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
			const GLuint firstIndex,
			const int materialIndex);

		constexpr GLuint getNumIndices() const; 
		constexpr GLuint getIndexOffset() const;
		constexpr GLuint getFirstIndex() const;

		constexpr int getMaterialIndex() const; 

	private:
		GLuint __numIndices{};

		/// <summary>
		/// mesh의 index buffer를 채울 때 각 인덱스에 더해주는 offset 값
		/// </summary>
		GLuint __indexOffset{};

		/// <summary>
		/// submesh draw시 시작할 index buffer 상의 인덱스
		/// </summary>
		GLuint __firstIndex{};

		int __materialIndex{ -1 };
	};
	
	constexpr SubmeshInfo::SubmeshInfo(
		const GLuint numIndices,
		const GLuint indexOffset,
		const GLuint firstIndex,
		const int materialIndex) :
		__numIndices{ numIndices }, 
		__indexOffset{ indexOffset },
		__firstIndex{ firstIndex },
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

	constexpr GLuint SubmeshInfo::getFirstIndex() const
	{
		return __firstIndex;
	}

	constexpr int SubmeshInfo::getMaterialIndex() const 
	{
		return __materialIndex;
	}
}