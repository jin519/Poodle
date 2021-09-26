#version 460 core

#include "constant_header.glsl"

uniform mat4 modelMat; 
uniform mat4 viewMat; 
uniform mat4 projectionMat; 

uniform uint attribFlag;

layout (location = positionAttribLocation) in vec3 position_;
layout (location = normalAttribLocation) in vec3 normal_; 
layout (location = tangentAttribLocation) in vec4 tangent_; 
layout (location = texcoordAttribLocation) in vec2 texcoord_; 
layout (location = colorAttribLocation) in vec4 color_; 
layout (location = jointsAttribLocation) in vec4 joints_; 
layout (location = weightsAttribLocation) in vec4 weights_; 

out vec2 texcoord; 
out flat uint hasTexcoord; 

out vec4 color;
out flat uint hasColor; 

void main() 
{
	const mat4 mvpMatrix = (projectionMat * viewMat * modelMat); 
	gl_Position = (mvpMatrix * vec4(position_, 1.f)); 

//	hasTexcoord = (attribFlag & texcoordAttribFlag);
//
//	if (hasTexcoord != 0U)
//		texcoord = texcoord_; 
//
//	hasColor = (attribFlag & colorAttribFlag);
//	
//	if (hasColor != 0U)
//		color = color_; 
}