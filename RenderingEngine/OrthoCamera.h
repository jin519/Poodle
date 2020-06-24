#pragma once

#include "TransformableCamera.h"
#include "Constant.h"

namespace Poodle 
{
	class OrthoCamera : public TransformableCamera
	{
	public:
		/* member function */
		constexpr void setOrthoHeight(const float height) noexcept;
		constexpr void adjustOrthoHeight(const float delta) noexcept;
		constexpr void setAspectRatio(const float ratio) noexcept;
		constexpr void setAspectRatio(const int width, const int height) noexcept;
		constexpr void setNear(const float zNear) noexcept;
		constexpr void setFar(const float zFar) noexcept;

	protected:
		/* member function */
		virtual void _onUpdateProjMatrix(glm::mat4& projMatrix) override;

	private:
		/* member variable */
		float __orthoHeight = Constant::Camera::DEFAULT_ORTHO_HEIGHT;
		float __aspectRatio = Constant::Camera::DEFAULT_ASPECT_RATIO;
		float __zNear = Constant::Camera::DEFAULT_Z_NEAR;
		float __zFar = Constant::Camera::DEFAULT_Z_FAR;
	};

	/* member function */
	constexpr void OrthoCamera::setOrthoHeight(const float height) noexcept 
	{
		__orthoHeight = clamp(
			height,
			Constant::Camera::MIN_ORTHO_HEIGHT,
			Constant::Camera::MAX_ORTHO_HEIGHT);
	}

	constexpr void OrthoCamera::adjustOrthoHeight(const float delta) noexcept 
	{
		setOrthoHeight(__orthoHeight + delta); 
	}

	constexpr void OrthoCamera::setAspectRatio(const float ratio) noexcept 
	{
		__aspectRatio = ratio;
	}

	constexpr void OrthoCamera::setAspectRatio(const int width, const int height) noexcept 
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