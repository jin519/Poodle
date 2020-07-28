#version 440 core

out vec4 fragmentColor;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	const vec3 INTENSITY = (objectColor * lightColor);
	fragmentColor = vec4(INTENSITY.rgb, 1.f);
} 