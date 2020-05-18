#version 440 core

in vec2 texCoordinate;
out vec4 fragmentColor;

uniform sampler2D tex;

void main()
{
	vec4 fetched = texture(tex, texCoordinate);
	fragmentColor = vec4(fetched.rgb, 1.f);
} 