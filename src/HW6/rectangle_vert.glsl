#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoordinate;
out vec2 outTexCoordinate;

void main()
{
    gl_Position = vec4(position, 1.f);
    outTexCoordinate = texCoordinate;
}