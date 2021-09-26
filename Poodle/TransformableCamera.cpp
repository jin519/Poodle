#include "TransformableCamera.h"
#include <glm/gtx/transform.hpp>

using namespace glm;

namespace Poodle
{
	void TransformableCamera::_onUpdateViewMatrix(mat4& viewMatrix)
	{
		__transform.updateMatrix();
		viewMatrix = inverse(__transform.getModelMatrix());
	}
}