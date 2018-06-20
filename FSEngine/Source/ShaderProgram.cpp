#include "../Header/ShaderProgram.h"
#include "../Header/AndUtility.h"
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
using namespace std;

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
	CreateShaders();
}

void ShaderProgram::CreateShaders()
{
	unsigned int vertexShaderId = CreateVertexShader();
	glAttachShader(shaderProgramId, vertexShaderId);

	unsigned int fragmentShaderId = CreateFragmentShader();
	glAttachShader(shaderProgramId, fragmentShaderId);

	LinkShaderProgram(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

unsigned int ShaderProgram::CreateVertexShader()
{
	char vertexShaderFallbackSource[] = {
		"#version 330 core\n"
		"layout (location = 0) in vec3 vertexPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(vertexPosition, 1.0);\n"
		"}\n"
	};

	return CreateShaderFromFilepath(GL_VERTEX_SHADER, "Resource/Shader/VertexShader.shader", vertexShaderFallbackSource);
}

unsigned int ShaderProgram::CreateFragmentShader()
{
	char fragmentShaderFallbackSource[] = {
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n"
	};

	return CreateShaderFromFilepath(GL_FRAGMENT_SHADER, "Resource/Shader/FragmentMixShader.shader", fragmentShaderFallbackSource);
}

unsigned int ShaderProgram::CreateShaderFromFilepath(unsigned int type, const char* filepath, const char* fallbackSource)
{
	int shaderId = TryCompileShaderSource(type, AndUtility::LoadTextFromFile(filepath).c_str());
	if (shaderId == -1)
	{
		shaderId = TryCompileShaderSource(type, fallbackSource);
		printf("Using fallback %s shader\n", GetShaderTypeText(type).c_str());
	}

	return shaderId;
}

int ShaderProgram::TryCompileShaderSource(unsigned int type, const char* source)
{
	unsigned int shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &source, NULL);

	int success;
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		printf("Warning: Unable to compile %s shader: %s\n", GetShaderTypeText(type).c_str(), infoLog);
		return -1;
	}

	return shaderId;
}

void ShaderProgram::LinkShaderProgram(const unsigned int vertexShaderId, const unsigned int fragmentShaderId)
{
	glLinkProgram(shaderProgramId);

	glDetachShader(shaderProgramId, vertexShaderId);
	glDetachShader(shaderProgramId, fragmentShaderId);

	int success;
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		throw (string)"Error linking program: " + infoLog;
	}
}

string ShaderProgram::GetShaderTypeText(unsigned int type)
{
	return (string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment");
}

unsigned int ShaderProgram::GetId()
{
	return shaderProgramId;
}

void ShaderProgram::Use()
{
	glUseProgram(shaderProgramId);
}

void ShaderProgram::SetBool(const char* name, bool value) const { glUniform1i(glGetUniformLocation(shaderProgramId, name), (int)value); }

void ShaderProgram::SetInt(const char* name, int value) const { glUniform1i(glGetUniformLocation(shaderProgramId, name), value); }

void ShaderProgram::SetFloat(const char* name, float value) const { glUniform1f(glGetUniformLocation(shaderProgramId, name), value); }

void ShaderProgram::SetMatrix(const char* name, mat4 value) const
{
	const int Count = 1;
	const bool Transpose = false;
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, name), Count, Transpose, value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
