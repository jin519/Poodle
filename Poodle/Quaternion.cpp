#include "Quaternion.h"
#include <exception>

using namespace glm;
using namespace std;

namespace Poodle
{
	Quaternion::Quaternion(const vec3& eulerAngles)
	{
		set(eulerAngles);
	}

	Quaternion::Quaternion(
		const float pitch, 
		const float yaw, 
		const float roll)
	{
		set(pitch, yaw, roll);
	}

	Quaternion::Quaternion(
		const float angle, 
		const vec3& axis)
	{
		set(angle, axis);
	}

	Quaternion::Quaternion(const mat3& rotationMatrix)
	{
		set(rotationMatrix);
	}

	Quaternion::Quaternion(const mat4& rotationMatrix)
	{
		set(rotationMatrix);
	}

	void Quaternion::set(const vec3& eulerAngles)
	{
		__quaternion = { eulerAngles };
	}

	void Quaternion::set(
		const float pitch, 
		const float yaw, 
		const float roll)
	{
		set({ pitch, yaw, roll });
	}

	void Quaternion::set(
		const float angle, 
		const vec3& axis)
	{
		__quaternion = angleAxis(angle, normalize(axis));
	}

	void Quaternion::set(const mat3& rotationMatrix)
	{
		__quaternion = normalize(quat_cast(rotationMatrix));
	}

	void Quaternion::set(const mat4& rotationMatrix)
	{
		__quaternion = normalize(quat_cast(rotationMatrix));
	}

	void Quaternion::orient(
		const vec3& forward_, 
		const vec3& referenceUp)
	{
		const vec3& forward = normalize(forward_);
		const vec3& up = normalize(referenceUp);

		if (epsilonEqual(fabsf(dot(forward, up)), 1.f, epsilon<float>()))
			throw exception{ "The forward_ vector and up vector are on a straight line." };

		const vec3& horizontal = normalize(cross(up, forward));
		const vec3& vertical = normalize(cross(forward, horizontal));

		__quaternion = quat(mat3{ horizontal, vertical, forward });
	}

	void Quaternion::rotateGlobal(const vec3& eularAngles)
	{
		__quaternion = normalize(quat{ eularAngles } * __quaternion);
	}

	void Quaternion::rotateGlobal(
		const float pitch, 
		const float yaw, 
		const float roll)
	{
		rotateGlobal({ pitch, yaw, roll });
	}

	void Quaternion::rotateGlobal(
		const float angle, 
		const vec3& axis)
	{
		__quaternion = normalize(angleAxis(angle, normalize(axis)) * __quaternion);
	}

	void Quaternion::rotateLocal(const vec3& eulerAngles)
	{
		rotateLocal(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	}

	void Quaternion::rotateLocal(
		const float pitch, 
		const float yaw, 
		const float roll)
	{
		const mat4& rotationMatrix = toMatrix();
		const vec3& basisX = rotationMatrix[0];
		const vec3& basisY = rotationMatrix[1];
		const vec3& basisZ = rotationMatrix[2];

		__quaternion = normalize(
			angleAxis(roll, basisZ) *
			angleAxis(yaw, basisY) *
			angleAxis(pitch, basisX) * 
			__quaternion);
	}

	void Quaternion::rotateFPS(
		const float pitch, 
		const float yaw, 
		const vec3& referenceUp)
	{
		const vec3& up = normalize(referenceUp);
		const vec3& horizontal = toMatrix()[0];
		const vec3& projUpHorizontal = (dot(horizontal, up) * up);
		const vec3& perpUpHorizontal = normalize(horizontal - projUpHorizontal);

		__quaternion = normalize(
			angleAxis(yaw, up) *
			angleAxis(pitch, perpUpHorizontal) * 
			__quaternion);
	}

	vec3 Quaternion::getEularAngles() const
	{
		return eulerAngles(__quaternion);
	}

	mat4 Quaternion::toMatrix() const
	{
		return mat4_cast(__quaternion);
	}

	pair<float, vec3> Quaternion::getAngleAxis() const
	{
		return { angle(__quaternion), axis(__quaternion) };
	}

	Quaternion operator*(
		const Quaternion& lhs, 
		const Quaternion& rhs)
	{
		return normalize(lhs.__quaternion * rhs.__quaternion);
	}
}