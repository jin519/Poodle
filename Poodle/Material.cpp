#include "Material.h"

using namespace std; 
using namespace GLCore; 

namespace Poodle 
{
	void Material::setDiffuseTexture(const shared_ptr<Texture2D>& pTexture)
	{
		__pDiffuseTexture = pTexture; 
	}
}