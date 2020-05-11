#version 440 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 _texCoordinate;

out vec2 texCoordinate;
uniform mat4 modelMat;

void main()
{
    gl_Position = (modelMat * vec4(position, 1.f));
    texCoordinate = _texCoordinate;
}