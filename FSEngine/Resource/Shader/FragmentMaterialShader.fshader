#version 330 core

in vec3 Normal;
in vec2 TexureCoord;
in vec3 FragmentPosition;
in float RenderPerspective;

struct Material
{
	vec3 specularColor;
	float shininessModifier;
};
uniform Material material;
uniform sampler2D diffuseTexture0;
uniform vec3 viewPosition;

out vec4 FragmentColor;

float ambientStrength = 0.8;
float diffuseStrength = 0.5;
float defaultShininess = 32;
float specularStrength = 0.25;

vec3 lightPosition = vec3(5, 5, 5);
vec3 lightColor = vec3(1, 1, 1);

vec3 CalcAmbient(vec3 diffuseColor)
{
	return lightColor * ambientStrength * diffuseColor;
}

vec3 CalcDiffuse(vec3 normal, vec3 lightDir, vec3 diffuseColor)
{
	float diffuse = max(dot(normal, lightDir), 0.0);
	return lightColor * (diffuse * diffuseStrength) * diffuseColor;
}

vec3 CalcSpecular(vec3 normal, vec3 lightDir)
{
	vec3 viewDir = normalize((-viewPosition) - FragmentPosition);
	vec3 reflectDir = reflect(-lightDir, normal);

	float shininess = defaultShininess * material.shininessModifier;
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	return specularStrength * specular * (lightColor * material.specularColor);
}

void main()
{
	if (RenderPerspective == 0)
	{
		FragmentColor = texture(diffuseTexture0, TexureCoord);
		return;
	}

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPosition - FragmentPosition);
	vec3 diffuseColor = vec3(texture(diffuseTexture0, TexureCoord));

	vec3 ambient = CalcAmbient(diffuseColor);
	vec3 diffuse = CalcDiffuse(normal, lightDir, diffuseColor);
	vec3 specular = CalcSpecular(normal, lightDir);

	FragmentColor = vec4(ambient + diffuse + specular, 1.0);
}
