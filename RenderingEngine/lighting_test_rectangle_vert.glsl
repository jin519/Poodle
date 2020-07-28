#version 440 core

layout (location = 0) in vec3 position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

void main()
{
    const mat4 MVP_MATRIX = (projectionMat * viewMat * modelMat); 
    gl_Position = (MVP_MATRIX * vec4(position, 1.f));
}