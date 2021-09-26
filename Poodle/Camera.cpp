#include "Camera.h"

namespace Poodle
{
	void Camera::update()
	{
		_onUpdateViewMatrix(__viewMat);
		_onUpdateProjMatrix(__projMat);
	}
}