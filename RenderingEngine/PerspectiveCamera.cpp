#include "PerspectiveCamera.h"

using namespace glm;

namespace Poodle 
{
	static mat4 myFrustum(const float left, const float right, const float bottom, const float top, const float zNear, const float zFar) 
	{
		const float RIGHT_SUB_LEFT = (right - left);
		const float TOP_SUB_BOTTOM = (top - bottom);
		const float NEAR_SUB_FAR = (zNear - zFar);
		const float TWO_NEAR = (2 * zNear);
		const float TWO_NEAR_FAR = (TWO_NEAR * zFar);

		return
		{
			(TWO_NEAR / RIGHT_SUB_LEFT), 0.f, 0.f, 0.f,
			0.f, (TWO_NEAR / TOP_SUB_BOTTOM), 0.f, 0.f,
			((right + left) / RIGHT_SUB_LEFT), ((top + bottom) / TOP_SUB_BOTTOM), ((zNear + zFar) / NEAR_SUB_FAR), -1.f, 
			0.f, 0.f, (TWO_NEAR_FAR / NEAR_SUB_FAR), 0.f
		};
	}

	static mat4 myPerspective(const float fov, const float aspectRatio, const float zNear, const float zFar) 
	{
		const float TOP = (zNear * tanf(0.5f * fov));
		const float RIGHT = (TOP * aspectRatio);

		return myFrustum(-RIGHT, RIGHT, -TOP, TOP, zNear, zFar);
	}

	/* member function */
	void PerspectiveCamera::_onUpdateProjMatrix(mat4& projMatrix)
	{
		projMatrix = perspective(__fov, __aspectRatio, __zNear, __zFar);
	}
}