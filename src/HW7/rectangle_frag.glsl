#version 460 core

in vec3 vertexColor;
in vec2 textureCoordinate; 
out vec4 fragmentColor;

uniform float mixRatio; 
uniform sampler2D tex;
uniform mat3 matrix;

void main()
{
	const vec2 CONVERTED_TEX_COORDINATE = (matrix * vec3(textureCoordinate, 1.f)).xy;
	const vec3 TEXTURE_COLOR = texture(tex, CONVERTED_TEX_COORDINATE).rgb;
	
	fragmentColor = vec4(mix(TEXTURE_COLOR, vertexColor.rgb, mixRatio), 1.f);
} 