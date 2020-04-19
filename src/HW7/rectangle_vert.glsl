#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 _vertexColor;
layout (location = 2) in vec2 _textureCoordinate;

out vec3 vertexColor;
out vec2 textureCoordinate;

void main()
{
    gl_Position = vec4(position, 1.f);
    vertexColor = _vertexColor;
    textureCoordinate = _textureCoordinate; 
}