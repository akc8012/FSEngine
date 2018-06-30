#version 330 core
out vec4 FragColor;

in vec2 texureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	FragColor = mix(texture(texture1, texureCoord), texture(texture2, texureCoord), 0.2);
}
