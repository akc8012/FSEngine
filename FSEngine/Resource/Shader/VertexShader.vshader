#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 normal; // to-do: implement this
layout(location = 2) in vec2 inTextureCoord;

out vec2 texureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool renderPerspective = true;

void main()
{
	mat4 viewMatrix = renderPerspective ? view : mat4(1);
	gl_Position = projection * viewMatrix * model * vec4(vertexPosition, 1.0);
	texureCoord = inTextureCoord;
}
