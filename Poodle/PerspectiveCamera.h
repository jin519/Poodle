#pragma once

#include "TransformableCamera.h"

namespace Poodle
{
	class PerspectiveCamera : public TransformableCamera
	{
	public:
		constexpr void setFov(const float fov) noexcept;

		constexpr void adjustFov(const float delta) noexcept;

		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(
			const int width, 
			const int height) noexcept;

		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

	protected:
		virtual void _onUpdateProjMatrix(glm::mat4& projMatrix) override;

	private:
		float __fov{ Constant::Camera::defaultFov };
		float __aspectRatio{ Constant::Camera::defaultAspectRatio };
		float __zNear{ Constant::Camera::defaultZNear };
		float __zFar{ Constant::Camera::defaultZFar };
	};

	constexpr void PerspectiveCamera::setFov(const float fov) noexcept
	{
		__fov = glm::clamp(
			fov, 
			Constant::Camera::minFov, 
			Constant::Camera::maxFov);
	}

	constexpr void PerspectiveCamera::adjustFov(const float delta) noexcept
	{
		setFov(__fov + delta);
	}

	constexpr void PerspectiveCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	constexpr void PerspectiveCamera::setAspectRatio(
		const int width, 
		const int height) noexcept
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