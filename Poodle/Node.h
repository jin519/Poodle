#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

namespace Poodle 
{
	class Node 
	{
	public:
		Node(
			const std::string& name,
			const glm::mat4& localJointMatrix); 

		constexpr const std::string& getName() const; 

		constexpr const glm::mat4& getStaticJointMatrix() const; 

		void addChildIndex(const int index);
		constexpr const std::vector<int>& getChildIndices() const;

	private:
		std::string __name; 

		glm::mat4 __staticJointMatrix{ 1.f };

		std::vector<int> __childIndices;

		int __meshIndex{ -1 }; 
	};

	constexpr const std::string& Node::getName() const
	{
		return __name; 
	}

	constexpr const glm::mat4& Node::getStaticJointMatrix() const
	{
		return __staticJointMatrix;
	}

	constexpr const std::vector<int>& Node::getChildIndices() const
	{
		return __childIndices; 
	}
}