#version 440 core

in vec3 normal;
out vec4 fragmentColor;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Light 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
};

uniform Material material;
uniform Light light;

vec3 calcAmbient() 
{
	return (material.ambient * light.ambient);
}

vec3 calcDiffuse() 
{
	const float POWER = clamp((dot(normal, -light.direction)), 0.f, 1.f);
	return (material.diffuse * light.diffuse * POWER);
}

vec3 calcSpecular() 
{
	return vec3(0.f);
}

void main()
{
	const vec3 AMBIENT = calcAmbient();
	const vec3 DIFFUSE = calcDiffuse();
	const vec3 SPECULAR = calcSpecular();
	const vec3 COLOR = (AMBIENT + DIFFUSE + SPECULAR);
	
	fragmentColor = vec4(COLOR, 1.f);
} 