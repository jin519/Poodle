#include "Quaternion.h"

using namespace glm;
using namespace std;

/* constructor */
Quaternion::Quaternion(const vec3& eulerAngles) : __quaternion(eulerAngles)
{}

Quaternion::Quaternion(const float pitch, const float yaw, const float roll) : Quaternion({ pitch, yaw, roll })
{}

Quaternion::Quaternion(const float angle, const vec3& axis) : __quaternion(angle, axis)
{}

Quaternion::Quaternion(const mat3& rotationMatrix) : __quaternion(rotationMatrix)
{}

Quaternion::Quaternion(const mat4& rotationMatrix) : __quaternion(rotationMatrix)
{}

/* member function */
void Quaternion::set(const vec3& eulerAngles) 
{
	__quaternion = eulerAngles;
}

void Quaternion::set(const float pitch, const float yaw, const float roll) 
{
	set({ pitch, yaw, roll });
}

void Quaternion::set(const float angle, const vec3& axis) 
{
	__quaternion = { angle, axis };
}

void Quaternion::set(const mat3& rotationMatrix) 
{
	__quaternion = rotationMatrix;
}

void Quaternion::set(const mat4& rotationMatrix) 
{
	__quaternion = rotationMatrix;
}

// 현재 객체를 forward 방향으로 틀음
void Quaternion::orient(const vec3& forward, const vec3& referenceUp = { 0.f, 1.f, 0.f }) 
{
		
}

// 절대 수치를 돌림
void Quaternion::rotateGlobal(const vec3& eularAngles) 
{
	
}

void Quaternion::rotateGlobal(const float pitch, const float yaw, const float roll) 
{
	
}

void Quaternion::rotateGlobal(const float angle, const vec3& axis) 
{
	
}

// 현재 객체 기저를 기준으로 돌림
void Quaternion::rotateLocal(const vec3& eulerAngles) 
{
	
}

void Quaternion::rotateLocal(const float pitch, const float yaw, const float roll) 
{
	
}

// 롤이 없음
// 업이 머가리 위로 고정
void Quaternion::rotateFPS(const float pitch, const float yaw, const vec3& referenceUp = { 0.f, 1.f, 0.f }) 
{
	
}

vec3 Quaternion::getEularAngles() const 
{
	return eulerAngles(__quaternion);
}

mat4 Quaternion::getMatrix() const 
{
	return mat4_cast(__quaternion);
}

pair<float, vec3> Quaternion::getAngleAxis() const 
{
	return { angle(__quaternion), axis(__quaternion) };
}

Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) 
{
	return (lhs.__quaternion * rhs.__quaternion);
}