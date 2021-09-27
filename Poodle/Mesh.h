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

		void addSubmeshInfo(std::unique_ptr<SubmeshInfo>&& pSubmeshInfo);

		void setVao(std::unique_ptr<GLCore::VertexArray>&& pVao); 

		// FIXME ----------

		Mesh(
			const VertexAttributeFlag attribFlag, 
			std::vector<std::unique_ptr<SubmeshInfo>>&& submeshInfo, 
			std::unique_ptr<GLCore::VertexArray>&& pVao);

		// ----------------

		constexpr VertexAttributeFlag getAttribFlag() const; 

		const SubmeshInfo* getSubmeshInfo(const size_t submeshIndex) const;
		
		constexpr const std::vector<std::unique_ptr<SubmeshInfo>>& getSubmeshInfo() const; 

		void draw(
			const GLsizei count, 
			const size_t first); 

	private:
		VertexAttributeFlag __attribFlag{ VertexAttributeFlag::NONE };

		std::vector<std::unique_ptr<SubmeshInfo>> __submeshInfoList; 

		std::unique_ptr<GLCore::VertexArray> __pVao;
	};

	constexpr Mesh::Mesh(const VertexAttributeFlag attribFlag) : 
		__attribFlag{ attribFlag }
	{}

	constexpr VertexAttributeFlag Mesh::getAttribFlag() const
	{
		return __attribFlag; 
	}

	constexpr const std::vector<std::unique_ptr<SubmeshInfo>>& Mesh::getSubmeshInfo() const
	{
		return __submeshInfoList; 
	}
}