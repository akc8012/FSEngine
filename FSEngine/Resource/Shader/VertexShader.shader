#version 330 core
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 inTextureCoord;

out vec2 texureCoord;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
	texureCoord = inTextureCoord;
}
