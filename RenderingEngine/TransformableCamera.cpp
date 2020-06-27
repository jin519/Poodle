#include "TransformableCamera.h"
#include <glm/gtx/transform.hpp>

using namespace glm;

namespace Poodle 
{
	/* member function */
	void TransformableCamera::_onUpdateViewMatrix(mat4& viewMatrix) 
	{
		__transform.updateMatrix();
		viewMatrix = inverse(__transform.getModelMatrix());
	}
}