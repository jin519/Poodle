#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Constant.h"
#include "Quaternion.h"

namespace Poodle
{
	class Transform
	{
	public:
		constexpr const glm::vec3& getPosition() const;
		
		constexpr void setPosition(const glm::vec3& position);
		constexpr void setPosition(
			const float x, 
			const float y, 
			const float z);
		
		constexpr void adjustPosition(const glm::vec3& delta);

		constexpr const Quaternion& getRotation() const;
		
		constexpr void setRotation(const glm::quat& src);
		constexpr void setRotation(
			const float w, 
			const float x, 
			const float y, 
			const float z);
		
		void setRotation(const glm::vec3& eulerAngles);
		void setRotation(
			const float pitch, 
			const float yaw, 
			const float roll);

		void setRotation(const glm::mat3& rotationMatrix);
		void setRotation(const glm::mat4& rotationMatrix);

		void orient(
			const glm::vec3& forward, 
			const glm::vec3& referenceUp = { 0.f, 1.f, 0.f });

		void rotateGlobal(const glm::vec3& eularAngles);
		void rotateGlobal(
			const float pitch, 
			const float yaw, 
			const float roll);

		void rotateGlobal(const float angle, const glm::vec3& axis);

		void rotateLocal(const glm::vec3& eulerAngles);
		void rotateLocal(
			const float pitch, 
			const float yaw, 
			const float roll);

		void rotateFPS(
			const float pitch, 
			const float yaw, 
			const glm::vec3& referenceUp = { 0.f, 1.f, 0.f });

		constexpr const glm::vec3& getScale() const;

		constexpr void setScale(const float value);

		constexpr void setScale(const glm::vec3& scale);
		constexpr void setScale(
			const float x, 
			const float y, 
			const float z);
		
		constexpr void adjustScale(const glm::vec3& delta);

		constexpr const glm::mat4& getModelMatrix() const;

		constexpr const glm::vec4& getBasisX() const;
		constexpr const glm::vec4& getBasisY() const;
		constexpr const glm::vec4& getBasisZ() const;

		constexpr void advanceX(const float delta);
		constexpr void advanceY(const float delta);
		constexpr void advanceZ(const float delta);

		void updateMatrix();

	private:
		glm::vec3 __position{ 0.f, 0.f, 0.f };
		Quaternion __rotation;
		glm::vec3 __scale{ 1.f, 1.f, 1.f };

		glm::mat4 __scaleMatrix{ 1.f };
		glm::mat4 __rotationMatrix{ 1.f };
		glm::mat4 __translationMatrix{ 1.f };
		glm::mat4 __modelMatrix{ 1.f };
	};

	constexpr const glm::vec3& Transform::getPosition() const
	{
		return __position;
	}

	constexpr void Transform::setPosition(const glm::vec3& position)
	{
		setPosition(position.x, position.y, position.z);
	}

	constexpr void Transform::setPosition(
		const float x,
		const float y,
		const float z)
	{
		__position.x = x;
		__position.y = y;
		__position.z = z;
	}

	constexpr void Transform::adjustPosition(const glm::vec3& delta)
	{
		setPosition(
			(__position.x + delta.x), 
			(__position.y + delta.y), 
			(__position.z + delta.z));
	}

	constexpr const Quaternion& Transform::getRotation() const
	{
		return __rotation;
	}

	constexpr void Transform::setRotation(const glm::quat& src)
	{
		__rotation.set(src);
	}

	constexpr void Transform::setRotation(
		const float w, 
		const float x, 
		const float y, 
		const float z)
	{
		__rotation.set(w, x, y, z);
	}

	constexpr const glm::vec3& Transform::getScale() const
	{
		return __scale;
	}

	constexpr void Transform::setScale(
		const float x, 
		const float y, 
		const float z)
	{
		__scale.x = glm::clamp(x, Constant::minScale, Constant::maxScale);
		__scale.y = glm::clamp(y, Constant::minScale, Constant::maxScale);
		__scale.z = glm::clamp(z, Constant::minScale, Constant::maxScale);
	}

	constexpr void Transform::setScale(const float value)
	{
		setScale(value, value, value);
	}

	constexpr void Transform::setScale(const glm::vec3& scale)
	{
		setScale(scale.x, scale.y, scale.z);
	}

	constexpr void Transform::adjustScale(const glm::vec3& delta)
	{
		setScale(
			(__scale.x + delta.x), 
			(__scale.y + delta.y), 
			(__scale.z + delta.z));
	}

	constexpr const glm::mat4& Transform::getModelMatrix() const
	{
		return __modelMatrix;
	}

	constexpr const glm::vec4& Transform::getBasisX() const
	{
		return __rotationMatrix[0];
	}

	constexpr const glm::vec4& Transform::getBasisY() const
	{
		return __rotationMatrix[1];
	}

	constexpr const glm::vec4& Transform::getBasisZ() const
	{
		return __rotationMatrix[2];
	}

	constexpr void Transform::advanceX(const float delta)
	{
		adjustPosition(getBasisX() * delta);
	}

	constexpr void Transform::advanceY(const float delta)
	{
		adjustPosition(getBasisY() * delta);
	}

	constexpr void Transform::advanceZ(const float delta)
	{
		adjustPosition(getBasisZ() * delta);
	}
}