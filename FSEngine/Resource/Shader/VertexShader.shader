#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 inTextureCoord;

out vec2 texureCoord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(vertexPosition, 1.0);
	texureCoord = inTextureCoord;
}
