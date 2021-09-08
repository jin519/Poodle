#version 460 core

#include "constant_header.glsl"

uniform uint attribFlag;

layout (location = positionAttribLocation) in vec3 position;
layout (location = normalAttribLocation) in vec3 normal; 
layout (location = tangentAttribLocation) in vec4 tangent; 
layout (location = texcoordAttribLocation) in vec2 texcoord; 
layout (location = colorAttribLocation) in vec4 color; 
layout (location = jointsAttribLocation) in vec4 joints; 
layout (location = weightsAttribLocation) in vec4 weights; 

out vec2 texcoord_; 
out vec4 color_;

void main() 
{
	if ((attribFlag & postionAttribFlag) != 0U)
		gl_Position = vec4(position, 1.f); 

	if ((attribFlag & colorAttribFlag) != 0U)
		color_ = color; 
}