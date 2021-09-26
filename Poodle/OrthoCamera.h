#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Poodle
{
	class OrthoCamera : public TransformableCamera
	{
	public:
		constexpr void setOrthoHeight(const float height) noexcept;
		
		constexpr void adjustOrthoHeight(const float delta) noexcept;

		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(
			const int width, 
			const int height) noexcept;

		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

	protected:
		virtual void _onUpdateProjMatrix(glm::mat4& projMatrix) override;

	private:
		float __orthoHeight{ Constant::Camera::defaultOrthoHeight };
		float __aspectRatio{ Constant::Camera::defaultAspectRatio };
		float __zNear{ Constant::Camera::defaultZNear };
		float __zFar{ Constant::Camera::defaultZFar };
	};

	constexpr void OrthoCamera::setOrthoHeight(const float height) noexcept
	{
		__orthoHeight = glm::clamp(
			height,
			Constant::Camera::minOrthoHeight,
			Constant::Camera::maxOrthoHeight);
	}

	constexpr void OrthoCamera::adjustOrthoHeight(const float delta) noexcept
	{
		setOrthoHeight(__orthoHeight + delta);
	}

	constexpr void OrthoCamera::setAspectRatio(const float ratio) noexcept
	{
		__aspectRatio = ratio;
	}

	constexpr void OrthoCamera::setAspectRatio(
		const int width, 
		const int height) noexcept
	{
		setAspectRatio((static_cast<float>(width) / static_cast<float>(height)));
	}

	constexpr void OrthoCamera::setNear(const float zNear) noexcept
	{
		__zNear = zNear;
	}

	constexpr void OrthoCamera::setFar(const float zFar) noexcept
	{
		__zFar = zFar;
	}
}