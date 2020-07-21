#include "OrthoCamera.h"

using namespace glm;

namespace Poodle 
{
	static mat4 myOrtho(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar) 
	{
		const float RIGHT_SUB_LEFT = (right - left);
		const float TOP_SUB_BOTTOM = (top - bottom);
		const float NEAR_SUB_FAR = (zNear - zFar);

		return 
		{ 
			(2.f / RIGHT_SUB_LEFT), 0.f, 0.f, 0.f, 
			0.f, (2.f / TOP_SUB_BOTTOM), 0.f, 0.f,
			0.f, 0.f, (2.f / NEAR_SUB_FAR), 0.f, 
			((right + left) / -RIGHT_SUB_LEFT), ((top + bottom) / -TOP_SUB_BOTTOM), ((zNear + zFar) / NEAR_SUB_FAR), 1.f
		};
	}

	/* member function */
	void OrthoCamera::_onUpdateProjMatrix(mat4& projMatrix) 
	{
		const float HEIGHT_HALF = (__orthoHeight * 0.5f);
		const float WIDTH_HALF = (__aspectRatio * __orthoHeight * 0.5f);

		projMatrix = ortho(-WIDTH_HALF, WIDTH_HALF, -HEIGHT_HALF, HEIGHT_HALF, __zNear, __zFar);
	}
}