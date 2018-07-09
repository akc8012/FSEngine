#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool renderPerspective;

out vec3 FragmentPosition;
out vec3 Normal;
out vec2 TexureCoord;
out float RenderPerspective;

void main()
{
	mat4 viewMatrix = renderPerspective ? view : mat4(1);
	gl_Position = projection * viewMatrix * model * vec4(position, 1.0);

	FragmentPosition = vec3(model * vec4(position, 1.0));
	Normal = normal;
	TexureCoord = textureCoord;

	RenderPerspective = renderPerspective ? 1 : 0;
}
