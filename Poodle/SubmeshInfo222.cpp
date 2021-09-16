#include "SubmeshInfo222.h"

using namespace std; 

namespace Poodle 
{
	void SubmeshInfo::setMaterial(const shared_ptr<Material>& pMaterial)
	{
		__pMaterial = pMaterial;
	}
}