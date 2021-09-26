#pragma once

#include "Camera.h"
#include "Transform.h"

namespace Poodle
{
	class TransformableCamera : public Camera
	{
	public:
		constexpr Transform& getTransform();
		constexpr const Transform& getTransform() const;

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4& viewMatrix) override;

	private:
		Transform __transform;
	};

	constexpr Transform& TransformableCamera::getTransform()
	{
		return __transform;
	}

	constexpr const Transform& TransformableCamera::getTransform() const
	{
		return __transform;
	}
}