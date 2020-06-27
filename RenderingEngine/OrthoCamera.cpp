#include "OrthoCamera.h"

using namespace glm;

namespace Poodle 
{
	/* member function */
	void OrthoCamera::_onUpdateProjMatrix(mat4& projMatrix) 
	{
		const float HEIGHT_HALF = (__orthoHeight * 0.5f);
		const float WIDTH_HALF = (__aspectRatio * __orthoHeight * 0.5f);

		projMatrix = ortho(-WIDTH_HALF, WIDTH_HALF, -HEIGHT_HALF, HEIGHT_HALF, __zNear, __zFar);
	}
}