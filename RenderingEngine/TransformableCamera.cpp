#include "TransformableCamera.h"
#include <glm/gtx/transform.hpp>

using namespace glm;

namespace Poodle 
{
	/* member function */
	void TransformableCamera::_onUpdateViewMatrix(mat4& viewMatrix) 
	{
		viewMatrix = transpose(__transform.getRotation().toMatrix()) * translate(-__transform.getPosition());
		__transform.updateMatrix();
	}
}