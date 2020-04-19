#version 460 core

in vec2 outTexCoordinate;
out vec4 fragColor;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
	vec4 fetched1 = texture(tex1, outTexCoordinate);
	vec4 fetched2 = texture(tex2, outTexCoordinate);

	fragColor = vec4(mix(fetched1.rgb, fetched2.rgb, 0.3f), 1.f);
} 