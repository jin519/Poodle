#include "Camera.h"

namespace Poodle 
{
	/* member function */
	void Camera::update() 
	{
		_onUpdateViewMatrix(__viewMat);
		_onUpdateProjMatrix(__projMat);
	}
}