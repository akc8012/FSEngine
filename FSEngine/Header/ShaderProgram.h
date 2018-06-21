#pragma once
#include "AndUtility.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
using namespace std;

class ShaderProgram
{
private:
	unsigned int shaderProgramId = NULL;

	unsigned int CreateVertexShader();
	unsigned int CreateFragmentShader();
	void LinkShaderProgram(const unsigned int vertexShaderId, const unsigned int fragmentShaderId);

	unsigned int CreateShaderFromFilepath(unsigned int type, const char* filepath, const char* fallbackSource);
	int TryCompileShaderSource(unsigned int type, const char* filepath);
	
	static string GetShaderTypeText(unsigned int type);

public:
	ShaderProgram();
	~ShaderProgram();

	void CreateShaders();
	void Use();
	unsigned int GetId();

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMatrix(const char* name, mat4 value) const;
};
