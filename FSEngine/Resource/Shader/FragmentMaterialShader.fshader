#version 330 core

in vec3 Normal;
in vec2 TexureCoord;
in vec3 FragmentPosition;
in float RenderPerspective;

uniform sampler2D diffuseTexture;

out vec4 FragmentColor;

float ambientStrength = 0.5;
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

void main()
{
	if (RenderPerspective == 0)
	{
		FragmentColor = texture(diffuseTexture, TexureCoord);
		return;
	}

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - FragmentPosition);

	vec3 ambient = CalcAmbient();
	vec3 diffuse = CalcDiffuse(normal, lightDirection);

	FragmentColor = vec4((ambient + diffuse) * vec3(texture2D(diffuseTexture, TexureCoord)), 1.0);
}
