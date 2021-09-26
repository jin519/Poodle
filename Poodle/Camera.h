#pragma once

#include <glm/glm.hpp>

namespace Poodle
{
	class Camera
	{
	public:
		constexpr const glm::mat4& getViewMatrix() const;
		constexpr const glm::mat4& getProjectionMatrix() const;

		void update();

	protected:
		virtual void _onUpdateViewMatrix(glm::mat4& viewMatrix) = 0;
		virtual void _onUpdateProjMatrix(glm::mat4& projMatrix) = 0;

	private:
		glm::mat4 __viewMat{ 1.f };
		glm::mat4 __projMat{ 1.f };
	};

	constexpr const glm::mat4& Camera::getViewMatrix() const
	{
		return __viewMat;
	}

	constexpr const glm::mat4& Camera::getProjectionMatrix() const
	{
		return __projMat;
	}
}