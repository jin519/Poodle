#version 440 core

in vec3 position;
in vec3 normal;
out vec4 fragmentColor;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light 
{
	uint type; // 0: directional, 1: point, 2: spot  
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 direction;
};

struct Camera 
{
	vec3 direction;
};

uniform Material material;
uniform Light light;
uniform Camera camera;

vec3 calcAmbient();
vec3 calcDiffuse();
vec3 calcSpecular();

void main()
{
	const vec3 AMBIENT = calcAmbient();
	const vec3 DIFFUSE = calcDiffuse();
	const vec3 SPECULAR = calcSpecular();
	const vec3 COLOR = (AMBIENT + DIFFUSE + SPECULAR);
	
	fragmentColor = vec4(COLOR, 1.f);
} 

vec3 calcAmbientDirectional() 
{
	return (material.ambient * light.ambient);
}

vec3 calcAmbientPoint() 
{
	return calcAmbientDirectional();
}

vec3 calcAmbientSpot() 
{
	return vec3(1.f);
}

vec3 calcAmbient() 
{
	switch (light.type) 
	{
	case 0:
		return calcAmbientDirectional();
	case 1:
		return calcAmbientPoint();
	case 2:
		return calcAmbientSpot();
	}
}

vec3 calcDiffuseDirectional() 
{
	const float POWER = clamp(dot(normal, -light.direction), 0.f, 1.f);
	return (material.diffuse * light.diffuse * POWER);
}

vec3 calcDiffusePoint() 
{
	const vec3 DIRECTION = normalize(position - light.position);
	const float POWER = clamp(dot(normal, -DIRECTION), 0.f, 1.f);

	return (material.diffuse * light.diffuse * POWER);
}

vec3 calcDiffuseSpot() 
{
	return vec3(0.f);
}

vec3 calcDiffuse() 
{
	switch (light.type) 
	{
	case 0:
		return calcDiffuseDirectional();
	case 1:
		return calcDiffusePoint(); 
	case 2:
		return calcDiffuseSpot(); 
	}
}

vec3 calcSpecularDirectional() 
{
	const vec3 REFLECTION_DIR = reflect(light.direction, normal);
	const float POWER = pow(max(dot(camera.direction, REFLECTION_DIR), 0.f), material.shininess);
	
	return (material.specular * light.specular * POWER); 
}

vec3 calcSpecularPoint() 
{
	const vec3 DIRECTION = normalize(position - light.position);
	const vec3 REFLECTION_DIR = reflect(DIRECTION, normal);
	const float POWER = pow(max(dot(camera.direction, REFLECTION_DIR), 0.f), material.shininess);
	
	return (material.specular * light.specular * POWER); 
}

vec3 calcSpecularSpot() 
{
	return vec3(0.f);
}

vec3 calcSpecular() 
{
	switch (light.type) 
	{
	case 0:
		return calcSpecularDirectional();
	case 1:
		return calcSpecularPoint();
	case 2:
		return calcSpecularSpot();
	}
}