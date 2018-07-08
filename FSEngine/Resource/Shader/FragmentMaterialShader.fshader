#version 330 core

in vec3 Normal;
in vec2 TexureCoord;
in vec3 FragPos;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;
uniform vec3 viewPosition;

out vec4 FragColor;

vec3 lightPosition = vec3(5, 5, 5);
vec3 lightColor = vec3(1, 1, 1);


vec3 CalcAmbient()
{
	float ambientStrength = 0.2;
	return lightColor * ambientStrength;
}

vec3 CalcDiffuse(vec3 normal, vec3 lightDir)
{
	float diffuse = max(dot(normal, lightDir), 0.0);

	float diffuseStrength = 0.5;
	return lightColor * (diffuse * diffuseStrength);
}

vec3 CalcSpecular(vec3 normal, vec3 lightDir)
{
	vec3 viewDir = normalize(-viewPosition - FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

	float shininess = 32;
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	float specularStrength = 0.25;
	return specularStrength * specular * lightColor;
}

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragPos);

	FragColor = vec4(CalcAmbient() + CalcDiffuse(normal, lightDir) + CalcSpecular(normal, lightDir), 1.0);
}
