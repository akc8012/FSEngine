#pragma once
#include "FileSystem.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>
#include <unordered_map>

class ShaderProgram
{
private:
	Uint32 shaderProgramId = NULL;
	std::unordered_map<std::string, Uint32> uniformLocations;
	bool renderPerspective = true;

	void CreateShaderProgram();

	Uint32 CreateVertexShader();
	Uint32 CreateFragmentShader();
	void LinkShaderProgram(const Uint32 vertexShaderId, const Uint32 fragmentShaderId);

	Uint32 CreateShaderFromFilepath(Uint32 type, const char* filepath, const char* fallbackSource);
	int TryCompileShaderSource(Uint32 type, const char* filepath);

	void MapUniformValues();
	Uint32 GetUniformLocation(const char* name) const;
	Uint32 GetUniformLocationFromGl(const char* name) const;

	static std::string GetShaderTypeText(Uint32 type);

public:
	ShaderProgram();
	~ShaderProgram();

	void CompileShaders();
	void Use();

	void SetBool(const char* name, bool value);
	void SetInt(const char* name, int value);
	void SetFloat(const char* name, float value);
	void SetMatrix(const char* name, mat4 value);

	void SetRenderPerspective(bool renderPerspective);
	bool RenderPerspective() const;
};
