#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Constant.h"

namespace Poodle
{
	class Transform
	{
	public:
		/* member function */
		constexpr const glm::vec3& getPosition() const;
		constexpr void setPosition(const float x, const float y, const float z);
		constexpr void setPosition(const glm::vec3& position);
		constexpr void adjustPosition(const glm::vec3& delta);
		constexpr const glm::vec3& getRotation() const;
		constexpr void setRotation(const float x, const float y, const float z);
		constexpr void setRotation(const glm::vec3& rotation);
		constexpr void adjustRotation(const glm::vec3& delta);
		constexpr const glm::vec3& getScale() const;
		constexpr void setScale(const float x, const float y, const float z);
		constexpr void setScale(const float value);
		constexpr void setScale(const glm::vec3& scale);
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
		/* member variable */
		glm::vec3 __position{ 0.f };
		glm::vec3 __rotation{ 0.f };
		glm::vec3 __scale{ 1.f };

		glm::mat4 __scaleMatrix{ 1.f };
		glm::mat4 __rotationMatrix{ 1.f };
		glm::mat4 __translationMatrix{ 1.f };
		glm::mat4 __modelMatrix{ 1.f };
	};

	constexpr const glm::vec3& Transform::getPosition() const
	{
		return __position;
	}

	constexpr void Transform::setPosition(const float x, const float y, const float z)
	{
		__position.x = x;
		__position.y = y;
		__position.z = z;
	}

	constexpr void Transform::setPosition(const glm::vec3& position)
	{
		setPosition(position.x, position.y, position.z);
	}

	constexpr void Transform::adjustPosition(const glm::vec3& delta)
	{
		setPosition((__position.x + delta.x), (__position.y + delta.y), (__position.z + delta.z));
	}

	constexpr const glm::vec3& Transform::getRotation() const
	{
		return __rotation;
	}

	constexpr void Transform::setRotation(const float x, const float y, const float z)
	{
		constexpr float TWO_PI = glm::two_pi<float>();

		// constexpr 접두사는 validateAngle 함수 포인터(람다 함수를 가리키는)를 리터럴 상수화 하겠다는 뜻
		// 뒤쪽의 -> float는 람다식에서 return type을 명시하는 문법. 
		// 생략시 return 구문을 통해 return type을 자동 추론함.
		constexpr auto validateAngle = [](const float angle) -> float
		{
			constexpr float TWO_PI = glm::two_pi<float>();

			if (angle < 0.f)
				return (angle + TWO_PI);
			else if (angle > TWO_PI)
				return  (angle - TWO_PI);

			return angle;
		};

		__rotation.x = validateAngle(x);
		__rotation.y = validateAngle(y);
		__rotation.z = validateAngle(z);
	}

	constexpr void Transform::setRotation(const glm::vec3& rotation)
	{
		setRotation(rotation.x, rotation.y, rotation.z);
	}

	constexpr void Transform::adjustRotation(const glm::vec3& delta)
	{
		setRotation((__rotation.x + delta.x), (__rotation.y + delta.y), (__rotation.z + delta.z));
	}

	constexpr const glm::vec3& Transform::getScale() const
	{
		return __scale;
	}

	constexpr void Transform::setScale(const float x, const float y, const float z)
	{
		__scale.x = glm::clamp(x, Constant::MIN_SCALE, Constant::MAX_SCALE);
		__scale.y = glm::clamp(y, Constant::MIN_SCALE, Constant::MAX_SCALE);
		__scale.z = glm::clamp(z, Constant::MIN_SCALE, Constant::MAX_SCALE);
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
		setScale((__scale.x + delta.x), (__scale.y + delta.y), (__scale.z + delta.z));
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