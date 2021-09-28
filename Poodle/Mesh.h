#pragma once

#include "VertexAttributeFlag.h"
#include "SubmeshInfo.h"
#include "../GLCore/VertexArray.h"

namespace Poodle
{
	class Mesh
	{
	public:
		constexpr Mesh(const VertexAttributeFlag attribFlag); 

		constexpr VertexAttributeFlag getAttribFlag() const; 

		constexpr size_t getNumSubmeshInfos() const;
		const SubmeshInfo* getSubmeshInfo(const size_t submeshInfoIndex) const;
		void setSubmeshInfos(std::vector<std::unique_ptr<SubmeshInfo>>&& submeshInfos);

		void setVao(std::unique_ptr<GLCore::VertexArray>&& pVao);

		void draw(const size_t submeshIndex);

	private:
		VertexAttributeFlag __attribFlag{ VertexAttributeFlag::NONE };

		std::vector<std::unique_ptr<SubmeshInfo>> __submeshInfos; 

		std::unique_ptr<GLCore::VertexArray> __pVao{};
	};

	constexpr Mesh::Mesh(const VertexAttributeFlag attribFlag) : 
		__attribFlag{ attribFlag }
	{}

	constexpr VertexAttributeFlag Mesh::getAttribFlag() const
	{
		return __attribFlag; 
	}

	constexpr size_t Mesh::getNumSubmeshInfos() const
	{
		return __submeshInfos.size(); 
	}
}