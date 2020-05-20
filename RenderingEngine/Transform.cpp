#include "Transform.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm; 

namespace Poodle
{
	void Transform::updateMatrix()
	{
		const mat4& SCALE_MATRIX = scale(__scale);
		const mat4& ROTATION_MATRIX = eulerAngleXYZ(__rotation.x, __rotation.y, __rotation.z);
		const mat4& TRANSLATION_MATRIX = translate(__position);

		__modelMatrix = (TRANSLATION_MATRIX * ROTATION_MATRIX * SCALE_MATRIX);
	}
}