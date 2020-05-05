#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 _vertexColor;

out vec3 vertexColor;
uniform mat4 transMat;

void main()
{
    gl_Position = (transMat * vec4(position, 1.f));
    vertexColor = _vertexColor;
}