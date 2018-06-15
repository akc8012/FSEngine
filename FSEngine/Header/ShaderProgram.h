#pragma once
#include <string>
using namespace std;

class ShaderProgram
{
private:
	unsigned int shaderProgramId = 0;

	unsigned int createVertexShader();
	unsigned int createFragmentShader();

	unsigned int createShaderFromFilepath(unsigned int type, const char* filepath, const char* fallbackSource);
	int tryCompileShaderSource(unsigned int type, const char* filepath);
	
	static string getShaderTypeText(unsigned int type);

public:
	ShaderProgram();
	~ShaderProgram();

	void createShaderProgram();
	unsigned int getId();
};
