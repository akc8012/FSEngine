#include "../Header/ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
	CreateShaders();
}

void ShaderProgram::CreateShaders()
{
	Uint32 vertexShaderId = CreateVertexShader();
	glAttachShader(shaderProgramId, vertexShaderId);

	Uint32 fragmentShaderId = CreateFragmentShader();
	glAttachShader(shaderProgramId, fragmentShaderId);

	LinkShaderProgram(vertexShaderId, fragmentShaderId);

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

Uint32 ShaderProgram::CreateVertexShader()
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

Uint32 ShaderProgram::CreateFragmentShader()
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

Uint32 ShaderProgram::CreateShaderFromFilepath(Uint32 type, const char* filepath, const char* fallbackSource)
{
	int shaderId = TryCompileShaderSource(type, AndUtility::LoadTextFromFile(filepath).c_str());
	if (shaderId == -1)
	{
		shaderId = TryCompileShaderSource(type, fallbackSource);
		printf("Using fallback %s shader\n", GetShaderTypeText(type).c_str());
	}

	return shaderId;
}

int ShaderProgram::TryCompileShaderSource(Uint32 type, const char* source)
{
	Uint32 shaderId = glCreateShader(type);
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

void ShaderProgram::LinkShaderProgram(const Uint32 vertexShaderId, const Uint32 fragmentShaderId)
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

string ShaderProgram::GetShaderTypeText(Uint32 type)
{
	return (string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment");
}

Uint32 ShaderProgram::GetId() const
{
	return shaderProgramId;
}

void ShaderProgram::Use()
{
	glUseProgram(shaderProgramId);
}

void ShaderProgram::SetBool(const char* name, bool value) const
{
	glUniform1i(GetUniformLocation(name), (int)value);
}

void ShaderProgram::SetInt(const char* name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloat(const char* name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

Uint32 ShaderProgram::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(shaderProgramId, name);
}

void ShaderProgram::SetMatrix(Uint32 uniformLocation, mat4 value) const
{
	const int Count = 1;
	const bool Transpose = false;
	glUniformMatrix4fv(uniformLocation, Count, Transpose, value_ptr(value));
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
