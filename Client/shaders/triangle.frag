#version 460 core

#include "constant_header.glsl"

uniform uint attribFlag; 

in vec4 color_; 
out vec4 color; 

void main() 
{
	if ((attribFlag & colorAttribFlag) != 0U)
		color = color_; 
	else
		color = vec4(1.f, 1.f, 1.f, 1.f); 
}