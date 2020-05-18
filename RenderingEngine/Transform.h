#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Constant.h"

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
	void updateMatrix();

private:
	/* member variable */
	glm::vec3 __position;
	glm::vec3 __rotation;
	glm::vec3 __scale;
	glm::mat4 __modelMatrix;
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
	__position += delta; 
}

constexpr const glm::vec3& Transform::getRotation() const
{
	return __rotation; 
}

constexpr void Transform::setRotation(const float x, const float y, const float z)
{
	constexpr float TWO_PI = glm::two_pi<float>();

	if (x < 0.f)
		__rotation.x = (x + TWO_PI);
	else if (x > TWO_PI)
		__rotation.x = (x - TWO_PI);
	else
		__rotation.x = x;

	if (y < 0.f)
		__rotation.y = (y + TWO_PI);
	else if (y > TWO_PI)
		__rotation.y = (y - TWO_PI);
	else
		__rotation.y = y;

	if (z < 0.f)
		__rotation.z = (z + TWO_PI);
	else if (z > TWO_PI)
		__rotation.z = (z - TWO_PI);
	else
		__rotation.z = z;
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
	__scale.x = x; 
	glm::clamp(__scale.x, MIN_SCALE, MAX_SCALE);

	__scale.y = y; 
	glm::clamp(__scale.y, MIN_SCALE, MAX_SCALE);

	__scale.z = z; 
	glm::clamp(__scale.z, MIN_SCALE, MAX_SCALE);
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