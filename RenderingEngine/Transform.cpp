#include "Transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm; 

namespace Poodle
{
	void Transform::updateMatrix()
	{
		__scaleMatrix = scale(__scale);
		__rotationMatrix = eulerAngleXYZ(__rotation.x, __rotation.y, __rotation.z);
		__translationMatrix = translate(__position);

		__modelMatrix = (__translationMatrix * __rotationMatrix * __scaleMatrix);
	}
}