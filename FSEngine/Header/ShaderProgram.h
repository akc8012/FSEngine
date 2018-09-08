#pragma once
#include "FileSystem.h"
#include "ParameterCollection.h"

#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
using glm::mat4;
using glm::mat3;
using glm::vec4;
using glm::vec3;

#include <string>
#include <unordered_map>
#include <memory>
using std::string;
using std::unordered_map;
using std::unique_ptr;
using std::make_unique;

class ShaderProgram
{
public:
	enum Parameters
	{
		IsUsing,
		RenderPerspective,
		EnableDepthTest,
		Blend,

		ParametersLength
	};

private:
	unique_ptr<ParameterCollection<Parameters, ParametersLength>> parameterCollection;

	Uint32 shaderProgramId = NULL;
	unordered_map<string, Uint32> uniformLocations;

	void CreateShaderProgram();
	void MapUniformValues();

	Uint32 CreateVertexShader();
	Uint32 CreateFragmentShader();
	void LinkShaderProgram(Uint32 vertexShaderId, Uint32 fragmentShaderId);

	Uint32 CreateShaderFromFilepath(Uint32 type, const string& filepath, const string& fallbackSource);
	int TryCompileShaderSource(Uint32 type, const string& filepath);

	Uint32 GetUniformLocation(const string& name);
	Uint32 GetUniformLocationFromGl(const string& name) const;
	void ShowUseWarning() const;

	static string GetShaderTypeText(Uint32 type);

public:
	ShaderProgram();
	~ShaderProgram();

	void CompileShaders();
	void Use();

	void SetBoolUniform(const string& name, bool value);
	void SetIntUniform(const string& name, int value);
	void SetFloatUniform(const string& name, float value);

	void SetVectorUniform(const string& name, const vec3& value);
	void SetVectorUniform(const string& name, const vec4& value);

	void SetMatrixUniform(const string& name, const mat3& value);
	void SetMatrixUniform(const string& name, const mat4& value);

	ParameterCollection<Parameters, ParametersLength>* GetParameterCollection() const;
};
