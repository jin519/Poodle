#pragma once

#include "TransformableCamera.h"

namespace Poodle 
{
	class PerspectiveCamera : public TransformableCamera
	{
	public:
		/* member function */
		constexpr void setFov(const float fov) noexcept;
		constexpr void adjustFov(const float delta) noexcept;
		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(const int width, const int height) noexcept;
		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

	protected:
		/* member function */
		virtual void _onUpdateProjMatrix(glm::mat4& projMatrix) override;

	private:
		/* member variable */
		float __fov = Constant::Camera::DEFAULT_FOV;
		float __aspectRatio = Constant::Camera::DEFAULT_ASPECT_RATIO;
		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;
	};

	/* member function */
	constexpr void PerspectiveCamera::setFov(const float fov) noexcept 
	{
		__fov = glm::clamp(fov, Constant::Camera::MIN_FOV, Constant::Camera::MAX_FOV);
	}

	constexpr void PerspectiveCamera::adjustFov(const float delta) noexcept 
	{	
		setFov(__fov + delta);
	}

	constexpr void PerspectiveCamera::setAspectRatio(const float ratio) noexcept 
	{
		__aspectRatio = ratio;
	}

	constexpr void PerspectiveCamera::setAspectRatio(const int width, const int height) noexcept 
	{
		setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
	}

	constexpr void PerspectiveCamera::setNear(const float zNear) noexcept 
	{
		__zNear = zNear;
	}

	constexpr void PerspectiveCamera::setFar(const float zFar) noexcept 
	{
		__zFar = zFar;
	}
}