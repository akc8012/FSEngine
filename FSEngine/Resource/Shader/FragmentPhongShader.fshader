#version 330 core

in vec3 Normal;
in vec2 TexureCoord;
in vec3 FragmentPosition;
in float RenderPerspective;

uniform sampler2D diffuseTexture;
uniform vec3 viewPosition;

out vec4 FragmentColor;

float ambientStrength = 0.5;
float specularStrength = 1;
float shininess = 32;

vec3 lightColor = vec3(1, 1, 1);
vec3 lightPosition = vec3(5, 5, 5);


vec3 CalcAmbient()
{
	return lightColor * ambientStrength;
}

vec3 CalcDiffuse(vec3 normal, vec3 lightDirection)
{
	float diffuse = max(dot(normal, lightDirection), 0.0);
	return diffuse * lightColor;
}

vec3 CalcSpecular(vec3 normal, vec3 lightDirection)
{
	vec3 viewDirection = normalize(-viewPosition - FragmentPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), shininess);

	return specularStrength * specular * lightColor;
}

vec3 CalcLighting()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragmentPosition);

	vec3 ambient = CalcAmbient();
	vec3 diffuse = CalcDiffuse(normal, lightDirection);
	vec3 specular = CalcSpecular(normal, lightDirection);

	return ambient + diffuse + specular;
}

void main()
{
	if (RenderPerspective == 0)
	{
		FragmentColor = texture(diffuseTexture, TexureCoord);
		return;
	}

	vec3 color = vec3(texture2D(diffuseTexture, TexureCoord));
	FragmentColor = vec4(CalcLighting() * color, 1.0);
}
