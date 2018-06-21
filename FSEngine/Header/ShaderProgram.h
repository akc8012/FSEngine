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
	Uint32 shaderProgramId = NULL;

	Uint32 CreateVertexShader();
	Uint32 CreateFragmentShader();
	void LinkShaderProgram(const Uint32 vertexShaderId, const Uint32 fragmentShaderId);

	Uint32 CreateShaderFromFilepath(Uint32 type, const char* filepath, const char* fallbackSource);
	int TryCompileShaderSource(Uint32 type, const char* filepath);
	
	static string GetShaderTypeText(Uint32 type);

public:
	ShaderProgram();
	~ShaderProgram();

	void CreateShaders();
	void Use();
	Uint32 GetId();

	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMatrix(const char* name, mat4 value) const;
};
