#pragma once

#include "VertexAttributeFlag.h"
#include "SubmeshInfo.h"
#include "../GLCore/VertexArray.h"

namespace Poodle
{
	class Mesh
	{
	public:
		Mesh(
			const VertexAttributeFlag attribFlag, 
			std::vector<std::unique_ptr<SubmeshInfo>>&& submeshInfo, 
			std::unique_ptr<GLCore::VertexArray>&& pVao);

		constexpr VertexAttributeFlag getAttribFlag() const; 

		const SubmeshInfo* getSubmeshInfo(const size_t submeshIndex) const; 

		const GLCore::VertexArray* getVao() const; 

	private:
		VertexAttributeFlag __attribFlag{ VertexAttributeFlag::NONE };

		std::vector<std::unique_ptr<SubmeshInfo>> __submeshInfo; 

		std::unique_ptr<GLCore::VertexArray> __pVao;
	};

	constexpr VertexAttributeFlag Mesh::getAttribFlag() const
	{
		return __attribFlag; 
	}
}