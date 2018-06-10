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

	uint createShaderFromFilepath(uint type, const char* filepath, const char* fallbackSource);
	int tryCompileShaderSource(uint type, const char* filepath);
	
	static string getShaderTypeText(uint type);

public:
	ShaderProgram();
	~ShaderProgram();

	void createShaderProgram();
	uint getShaderProgramId();
};
