#pragma once

#include "Material.h"

namespace Poodle 
{
	class SubmeshInfo 
	{
	public:
		constexpr SubmeshInfo(
			const GLuint numIndices,
			const GLuint indexOffset);

		constexpr GLuint getNumIndices() const; 

		constexpr GLuint getIndexOffset() const; 

		constexpr const std::shared_ptr<Material>& getMaterial() const; 
		void setMaterial(const std::shared_ptr<Material>& pMaterial); 

	private:
		GLuint __numIndices{};
		GLuint __indexOffset{};
		
		std::shared_ptr<Material> __pMaterial{};
	};
	
	constexpr SubmeshInfo::SubmeshInfo(
		const GLuint numIndices,
		const GLuint indexOffset) :
		__numIndices{ numIndices }, 
		__indexOffset{ indexOffset }
	{}

	constexpr GLuint SubmeshInfo::getNumIndices() const
	{
		return __numIndices;
	}

	constexpr GLuint SubmeshInfo::getIndexOffset() const
	{
		return __indexOffset; 
	}

	constexpr const std::shared_ptr<Material>& SubmeshInfo::getMaterial() const
	{
		return __pMaterial; 
	}
}