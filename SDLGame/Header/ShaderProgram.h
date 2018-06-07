#pragma once

#define uint unsigned int

class ShaderProgram
{
private:
	uint shaderProgramId = 0;

	uint createVertexShader();
	uint createFragmentShader();
	uint createShader(uint type, const char* source);

public:
	ShaderProgram();
	~ShaderProgram();

	uint getShaderProgramId();
};
