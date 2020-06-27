#include "PerspectiveCamera.h"

using namespace glm;

namespace Poodle 
{
	/* member function */
	void PerspectiveCamera::_onUpdateProjMatrix(mat4& projMatrix)
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}
}