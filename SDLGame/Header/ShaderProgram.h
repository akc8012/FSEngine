#pragma once
#include <string>

#define uint unsigned int

class ShaderProgram
{
private:
	uint shaderProgramId = 0;

	uint createVertexShader();
	uint createFragmentShader();
	uint createShader(uint type, const char* source);
	std::string readShaderSourceFromFile(const char* filePath);

public:
	ShaderProgram();
	~ShaderProgram();

	uint getShaderProgramId();
};
