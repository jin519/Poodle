#version 460 core

#include "constant_header.glsl"

uniform uint attribFlag;
uniform bool hasDiffuseTex; 
uniform sampler2D diffuseTex; 

in vec2 texcoord;
in flat uint hasTexcoord; 

in vec4 color; 
in flat uint hasColor; 

out vec4 fragColor; 

void main() 
{
	if (hasTexcoord != 0U)
	{
		if (hasDiffuseTex)
			fragColor = vec4(texture(diffuseTex, texcoord).rgb, 1.f); 
		else
			fragColor = vec4(1.f, 1.f, 1.f, 1.f); 
	}

//	if (hasTexcoord != 0U)
//	{
//		vec4 fetched = texture(tex, texcoord);
//
//		if (hasColor != 0U)
//			fragColor = vec4(mix(color.rgb, fetched.rgb, 0.7f), 1.f);
//		else
//			fragColor = vec4(fetched.rgb, 1.f); 
//	}
//	else if (hasColor != 0U)
//		fragColor = color; 
//	else
//		fragColor = vec4(1.f, 1.f, 1.f, 1.f); 
}