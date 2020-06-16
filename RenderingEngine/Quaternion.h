#pragma once

#include <glm/gtx/quaternion.hpp>
#include <utility>

class Quaternion 
{
public:
	/* constructor */
	Quaternion() = default;
	Quaternion(const Quaternion& src) = default;
	constexpr Quaternion(const glm::quat& src);
	constexpr Quaternion(const float w, const float x, const float y, const float z);
	Quaternion(const glm::vec3& eulerAngles);
	Quaternion(const float pitch, const float yaw, const float roll);
	Quaternion(const float angle, const glm::vec3& axis);
	Quaternion(const glm::mat3& rotationMatrix);
	Quaternion(const glm::mat4& rotationMatrix);

	/* member function */
	constexpr void set(const glm::quat& src);
	constexpr void set(const float w, const float x, const float y, const float z);
	void set(const glm::vec3& eulerAngles);
	void set(const float pitch, const float yaw, const float roll);
	void set(const float angle, const glm::vec3& axis);
	void set(const glm::mat3& rotationMatrix);
	void set(const glm::mat4& rotationMatrix);
	void orient(const glm::vec3& forward, const glm::vec3& referenceUp = { 0.f, 1.f, 0.f });
	void rotateGlobal(const glm::vec3& eularAngles);
	void rotateGlobal(const float pitch, const float yaw, const float roll);
	void rotateGlobal(const float angle, const glm::vec3& axis);
	void rotateLocal(const glm::vec3& eulerAngles);
	void rotateLocal(const float pitch, const float yaw, const float roll);
	void rotateFPS(const float pitch, const float yaw, const glm::vec3& referenceUp = { 0.f, 1.f, 0.f });
	glm::vec3 getEularAngles() const;
	glm::mat4 getMatrix() const;
	std::pair<float, glm::vec3> getAngleAxis() const;
	friend Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);

private:
	/* member variable */
	glm::quat __quaternion = { 1.f, 0.f, 0.f, 0.f };
};

/* constructor */
constexpr Quaternion::Quaternion(const glm::quat& src) : __quaternion(src)
{}

constexpr Quaternion::Quaternion(const float w, const float x, const float y, const float z) : Quaternion({ w, x, y, z })
{}

/* member function */
constexpr void Quaternion::set(const glm::quat& src)
{
	__quaternion = src;
}

constexpr void Quaternion::set(const float w, const float x, const float y, const float z) 
{
	set({ w, x, y, z });
}