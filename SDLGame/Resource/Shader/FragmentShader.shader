#version 330 core
out vec4 FragColor;

in vec2 texureCoord;

uniform sampler2D textureSampler;

void main()
{
	FragColor = texture(textureSampler, texureCoord);
}
