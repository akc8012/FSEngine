#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

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

	void setBool(const char* name, bool value) const;
	void setInt(const char* name, int value) const;
	void setFloat(const char* name, float value) const;
	void setMatrix(const char* name, mat4 value) const;
};
