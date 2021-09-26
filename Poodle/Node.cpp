#include "Node.h"

using namespace std; 
using namespace glm;

namespace Poodle 
{
	Node::Node(
		const string& name,
		const mat4& localJointMatrix) : 
		__name{ name }, 
		__staticJointMatrix{ localJointMatrix }
	{}

	void Node::addChildIndex(const int index)
	{
		__childIndices.emplace_back(index); 
	}
}