#version 330 core

layout(location = 0) in vec3 positionVector;
layout(location = 1) in vec3 normalVector;
layout(location = 2) in vec2 textureCoordVector;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform bool renderPerspective;

uniform mat3 normalMatrix;

out vec3 FragmentPosition;
out vec3 Normal;
out vec2 TexureCoord;


void main()
{
	vec4 fragmentPositionVector = modelMatrix * vec4(positionVector, 1);

	FragmentPosition = vec3(fragmentPositionVector);
	Normal = normalMatrix * normalVector;
	TexureCoord = textureCoordVector;

	gl_Position = projectionMatrix * (renderPerspective ? viewMatrix : mat4(1))  * fragmentPositionVector;
}
