#version 460 core

out vec4 fragColor;
layout (location = 0) uniform vec3 triangleColor;

void main()
{
    fragColor = vec4(triangleColor, 1.f);
} 