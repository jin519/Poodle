#pragma once

#include "Camera.h"
#include "Transform.h"

namespace Poodle 
{
	class TransformableCamera abstract : public Camera
	{
	public:
		/* member function */
		constexpr Transform& getTransform();
		constexpr const Transform& getTransform() const;

	protected:
		/* member function */
		virtual void _onUpdateViewMatrix(glm::mat4& viewMatrix) override;

	private:
		/* member variable */
		Transform __transform;
	};

	/* member function */
	constexpr Transform& TransformableCamera::getTransform() 
	{
		return __transform;
	}

	constexpr const Transform& TransformableCamera::getTransform() const 
	{
		return __transform;
	}
}