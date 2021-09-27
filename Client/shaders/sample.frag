#version 460 core

#include "constant_header.glsl"

uniform uint hasDiffuseTex; 
uniform sampler2D diffuseTex;
uniform float diffuseTexBlendFactor;

in vec2 texcoord;
in flat uint hasTexcoord; 

in vec4 color; 
in flat uint hasColor; 

out vec4 fragColor; 

void main() 
{
	if (hasTexcoord != 0U)
	{
		if (hasDiffuseTex != 0U)
		{
			const vec3 diffuse = texture(diffuseTex, texcoord).rgb; 
			fragColor = vec4(diffuse, 1.f); 
		}
	}
	else if (hasColor != 0U)
		fragColor = color; 
	else
		fragColor = vec4(1.f, 1.f, 1.f, 1.f); 
}