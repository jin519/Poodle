#include "Transform.h"
#include <glm/gtx/transform.hpp>

using namespace glm; 

namespace Poodle
{
	/* member function */
	void Transform::setRotation(const float pitch, const float yaw, const float roll)
	{
		constexpr float TWO_PI = glm::two_pi<float>();

		constexpr auto validateAngle = [](const float angle) -> float
		{
			constexpr float TWO_PI = glm::two_pi<float>();

			if (angle < 0.f)
				return (angle + TWO_PI);
			else if (angle > TWO_PI)
				return  (angle - TWO_PI);

			return angle;
		};

		__rotation.set(validateAngle(pitch), validateAngle(yaw), validateAngle(roll));
	}

	void Transform::setRotation(const glm::vec3& eulerAngles)
	{
		setRotation(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	}

	void Transform::setRotation(const mat3& rotationMatrix) 
	{
		__rotation.set(rotationMatrix);
	}

	void Transform::setRotation(const mat4& rotationMatrix) 
	{
		__rotation.set(rotationMatrix);
	}

	void Transform::orient(const vec3& forward, const vec3& referenceUp)
	{
		__rotation.orient(forward, referenceUp);
	}

	void Transform::rotateGlobal(const vec3& eularAngles) 
	{
		__rotation.rotateGlobal(eularAngles);
	}

	void Transform::rotateGlobal(const float pitch, const float yaw, const float roll) 
	{
		__rotation.rotateGlobal(pitch, yaw, roll);
	}

	void Transform::rotateGlobal(const float angle, const vec3& axis) 
	{
		__rotation.rotateGlobal(angle, axis);
	}

	void Transform::rotateLocal(const vec3& eulerAngles) 
	{
		__rotation.rotateLocal(eulerAngles);
	}

	void Transform::rotateLocal(const float pitch, const float yaw, const float roll) 
	{
		__rotation.rotateLocal(pitch, yaw, roll);
	}

	void Transform::rotateFPS(const float pitch, const float yaw, const vec3& referenceUp) 
	{
		__rotation.rotateFPS(pitch, yaw, referenceUp);
	}

	void Transform::updateMatrix()
	{
		__scaleMatrix = scale(__scale);
		__rotationMatrix = __rotation.toMatrix(); 
		__translationMatrix = translate(__position);

		__modelMatrix = (__translationMatrix * __rotationMatrix * __scaleMatrix);
	}
}