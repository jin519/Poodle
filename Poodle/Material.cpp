#include "Material.h"

using namespace glm; 

namespace Poodle 
{
    void Material::setDiffuseColor(const vec3& diffuseColor)
	{
		__diffuseColor = diffuseColor; 
	}
}