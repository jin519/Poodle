#include "OrthoCamera.h"

using namespace glm;

namespace Poodle
{
	static mat4 myOrtho(
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

		return
		{
			(2.f / width), 0.f, 0.f, 0.f,
			0.f, (2.f / height), 0.f, 0.f,
			0.f, 0.f, (2.f / depth), 0.f,
			((right + left) / -width), ((top + bottom) / -height), ((zNear + zFar) / depth), 1.f
		};
	}

	void OrthoCamera::_onUpdateProjMatrix(mat4& projMatrix)
	{
		const float heightHalf = (__orthoHeight * 0.5f);
		const float widthHalf = (__aspectRatio * __orthoHeight * 0.5f);

		projMatrix = ortho(
			-widthHalf, 
			widthHalf, 
			-heightHalf, 
			heightHalf, 
			__zNear, 
			__zFar);
	}
}