#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inColor;
layout (location = 0) uniform float displacement;

out vec3 outColor;

void main()
{
    const float SIN_DISPLACEMENT = sin(displacement);
    const float COS_DISPLACEMENT = cos(displacement);

    const mat3 ROTATION_MATRIX = mat3(
    COS_DISPLACEMENT, -SIN_DISPLACEMENT, 0.f,
    SIN_DISPLACEMENT, COS_DISPLACEMENT, 0.f,
    0.f, 0.f, 1.f);

    const vec3 ROTATED_POSITION = (ROTATION_MATRIX * position);
    gl_Position = vec4(ROTATED_POSITION, 1.f); 

    outColor = inColor;
}