#version 440 core

layout (location = 0) in vec3 _position;
layout (location = 1) in vec3 _normal;
out vec3 position;
out vec3 normal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    const vec4 WORLD_POS = (modelMat * vec4(_position, 1.f));
    gl_Position = (projectionMat * viewMat) * WORLD_POS;
    position = WORLD_POS.xyz;

    const mat3 NORMAL_MODEL_MAT = transpose(inverse(mat3(modelMat)));
    normal = (NORMAL_MODEL_MAT * _normal);
}