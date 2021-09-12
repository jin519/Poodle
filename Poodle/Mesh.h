#pragma once

#include "VertexAttributeFlag.h"
#include "SubMeshInfo.h"
#include "../GLCore/VertexArray.h"
#include <vector>
#include <memory>

namespace Poodle 
{
	class Mesh 
	{
	public:
		Mesh() = default; 
		explicit Mesh(std::unique_ptr<GLCore::VertexArray>&& pVao) noexcept; 

		constexpr VertexAttributeFlag getAttribFlag() const;
		constexpr void setAttribFlag(const VertexAttributeFlag attribFlag);

		void addSubMeshInfo(
			const GLuint numIndices,
			const GLuint indexOffset);

	private:
		VertexAttributeFlag __attribFlag; 

		std::vector<std::unique_ptr<SubMeshInfo>> __subMeshInfoList; 
		std::unique_ptr<GLCore::VertexArray> __pVao;
	};

	constexpr VertexAttributeFlag Mesh::getAttribFlag() const
	{
		return __attribFlag;
	}

	constexpr void Mesh::setAttribFlag(const VertexAttributeFlag attribFlag)
	{
		__attribFlag = attribFlag;
	}
}