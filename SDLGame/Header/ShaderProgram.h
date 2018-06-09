#pragma once
#include <string>
using namespace std;

#define uint unsigned int

class ShaderProgram
{
private:
	uint shaderProgramId = 0;

	uint createVertexShader();
	uint createFragmentShader();
	uint createShader(uint type, const char* source);
	string readShaderSourceFromFile(const char* filepath);

public:
	ShaderProgram();
	~ShaderProgram();

	uint getShaderProgramId();
};
