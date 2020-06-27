#include "Quaternion.h"
#include "QuaternionException.h"

using namespace glm;
using namespace std;

namespace Poodle 
{
	/* constructor */
	Quaternion::Quaternion(const vec3& eulerAngles)
	{
		set(eulerAngles);
	}

	Quaternion::Quaternion(const float pitch, const float yaw, const float roll)
	{
		set(pitch, yaw, roll);
	}

	Quaternion::Quaternion(const float angle, const vec3& axis)
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

	/* member function */
	void Quaternion::set(const vec3& eulerAngles)
	{
		__quaternion = { eulerAngles };
	}

	void Quaternion::set(const float pitch, const float yaw, const float roll)
	{
		set({ pitch, yaw, roll });
	}

	void Quaternion::set(const float angle, const vec3& axis)
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

	void Quaternion::orient(const vec3& forward, const vec3& referenceUp)
	{
		const vec3& FORWARD = normalize(forward);
		const vec3& UP = normalize(referenceUp);

		if (epsilonEqual(fabsf(dot(FORWARD, UP)), 1.f, epsilon<float>()))
			throw QuaternionException("The forward vector and up vector are on a straight line.");

		const vec3& HORIZONTAL = normalize(cross(UP, FORWARD));
		const vec3& VERTICAL = normalize(cross(FORWARD, HORIZONTAL));

		__quaternion = quat(mat3{ HORIZONTAL, VERTICAL, FORWARD });
	}

	void Quaternion::rotateGlobal(const vec3& eularAngles)
	{
		__quaternion = normalize(quat{ eularAngles } * __quaternion);
	}

	void Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll)
	{
		rotateGlobal({ pitch, yaw, roll });
	}

	void Quaternion::rotateGlobal(const float angle, const vec3& axis)
	{
		__quaternion = normalize(angleAxis(angle, normalize(axis)) * __quaternion);
	}

	void Quaternion::rotateLocal(const vec3& eulerAngles)
	{
		rotateLocal(eulerAngles.x, eulerAngles.y, eulerAngles.z);
	}

	void Quaternion::rotateLocal(const float pitch, const float yaw, const float roll)
	{
		const mat4& ROTATION_MATRIX = toMatrix(); 
		const vec3& BASIS_X = ROTATION_MATRIX[0];
		const vec3& BASIS_Y = ROTATION_MATRIX[1];
		const vec3& BASIS_Z = ROTATION_MATRIX[2];

		__quaternion = normalize(
			angleAxis(roll, BASIS_Z) * 
			angleAxis(yaw, BASIS_Y) * 
			angleAxis(pitch, BASIS_X) * __quaternion);
	}

	void Quaternion::rotateFPS(const float pitch, const float yaw, const vec3& referenceUp)
	{
		const vec3& UP = normalize(referenceUp);
		const vec3& HORIZONTAL = toMatrix()[0];
		const vec3& PROJ_UP_HORIZONTAL = (dot(HORIZONTAL, UP) * UP);
		const vec3& PERP_UP_HORIZONTAL = normalize(HORIZONTAL - PROJ_UP_HORIZONTAL);

		__quaternion = normalize(
			angleAxis(yaw, UP) *
			angleAxis(pitch, PERP_UP_HORIZONTAL) * __quaternion);
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

	Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
	{
		return normalize(lhs.__quaternion * rhs.__quaternion);
	}
}