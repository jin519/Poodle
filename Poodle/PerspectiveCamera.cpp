#include "PerspectiveCamera.h"

using namespace glm;

namespace Poodle
{
	static mat4 myFrustum(
		const float left, 
		const float right, 
		const float bottom, 
		const float top, 
		const float zNear, 
		const float zFar)
	{
		const float width = (right - left);
		const float height = (top - bottom);
		const float depth = (zNear - zFar);
		const float twoNear = (2.f * zNear);
		const float twoNearFar = (twoNear * zFar);

		return
		{
			(twoNear / width), 0.f, 0.f, 0.f,
			0.f, (twoNear / height), 0.f, 0.f,
			((right + left) / width), ((top + bottom) / height), ((zNear + zFar) / depth), -1.f,
			0.f, 0.f, (twoNearFar / depth), 0.f
		};
	}

	static mat4 myPerspective(
		const float fov, 
		const float aspectRatio, 
		const float zNear, 
		const float zFar)
	{
		const float top = (zNear * tanf(0.5f * fov));
		const float right = (top * aspectRatio);

		return myFrustum(-right, right, -top, top, zNear, zFar);
	}

	void PerspectiveCamera::_onUpdateProjMatrix(mat4& projMatrix)
	{
		projMatrix = perspective(
			__fov, 
			__aspectRatio, 
			__zNear, 
			__zFar);
	}
}