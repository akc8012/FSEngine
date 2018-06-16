#pragma once
#include <string>
using namespace std;

class ShaderProgram
{
private:
	unsigned int shaderProgramId = NULL;

	unsigned int createVertexShader();
	unsigned int createFragmentShader();
	void linkShaderProgram(const unsigned int vertexShaderId, const unsigned int fragmentShaderId);

	unsigned int createShaderFromFilepath(unsigned int type, const char* filepath, const char* fallbackSource);
	int tryCompileShaderSource(unsigned int type, const char* filepath);
	
	static string getShaderTypeText(unsigned int type);

public:
	ShaderProgram();
	~ShaderProgram();

	void createShaders();
	unsigned int getId();
	void use();
};
