#include "Model.h"

using namespace std; 

namespace Poodle 
{
	Model::Model(
		const string_view& name,
		const int rootNodeIndex,
		vector<unique_ptr<Node>>&& nodes, 
		vector<shared_ptr<Material>>&& materials, 
		vector<shared_ptr<Mesh>>&& meshes) :
		__name{ name }, 
		__rootNodeIndex{ rootNodeIndex }, 
		__nodes{ move(nodes) }, 
		__materials{ move(materials) }, 
		__meshes{ move(meshes) }
	{}
}