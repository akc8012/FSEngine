#include "../Header/ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
	CompileShaders();
}

void ShaderProgram::CompileShaders()
{
	isUsing = false;
	CreateShaderProgram();

	uniformLocations.clear();
	MapUniformValues();
	Use();
}

void ShaderProgram::MapUniformValues()
{
	string uniformNames[] = { "modelMatrix", "viewMatrix", "projectionMatrix", "normalMatrix", "renderPerspective", "diffuseTexture", "flatColor", "viewPosition" };
	for (const auto& uniformName : uniformNames)
		uniformLocations[uniformName] = GetUniformLocationFromGl(uniformName.c_str());
}

void ShaderProgram::CreateShaderProgram()
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

	return CreateShaderFromFilepath(GL_VERTEX_SHADER, "Resource/Shader/VertexShader.glsl", vertexShaderFallbackSource);
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

	return CreateShaderFromFilepath(GL_FRAGMENT_SHADER, "Resource/Shader/FragmentPhongShader.glsl", fragmentShaderFallbackSource);
}

Uint32 ShaderProgram::CreateShaderFromFilepath(Uint32 type, const string& filepath, const string& fallbackSource)
{
	int shaderId = TryCompileShaderSource(type, FileSystem::LoadTextFromFile(filepath).c_str());
	if (shaderId == -1)
	{
		shaderId = TryCompileShaderSource(type, fallbackSource);
		printFS("Using fallback " + GetShaderTypeText(type) + " shader");
	}

	return shaderId;
}

int ShaderProgram::TryCompileShaderSource(Uint32 type, const string& source)
{
	Uint32 shaderId = glCreateShader(type);

	const char* sourceText = source.c_str();
	glShaderSource(shaderId, 1, &sourceText, NULL);

	int success;
	glCompileShader(shaderId);
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		printFS("Warning: Unable to compile " + GetShaderTypeText(type) + " shader: " + infoLog);
		return -1;
	}

	return shaderId;
}

void ShaderProgram::LinkShaderProgram(Uint32 vertexShaderId, Uint32 fragmentShaderId)
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
		throwFS((string)"Error linking program: " + infoLog);
	}
}

string ShaderProgram::GetShaderTypeText(Uint32 type)
{
	return (string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment");
}

void ShaderProgram::Use()
{
	isUsing = true;
	glUseProgram(shaderProgramId);
}

void ShaderProgram::SetBoolUniform(const string& name, bool value)
{
	ShowUseWarning();
	glUniform1i(GetUniformLocation(name), (int)value);
}

void ShaderProgram::SetIntUniform(const string& name, int value)
{
	ShowUseWarning();
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloatUniform(const string& name, float value)
{
	ShowUseWarning();
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetVectorUniform(const string& name, const vec3& value)
{
	ShowUseWarning();

	const int Count = 1;
	glUniform3fv(GetUniformLocation(name), Count, value_ptr(value));
}

void ShaderProgram::SetVectorUniform(const string& name, const vec4& value)
{
	ShowUseWarning();

	const int Count = 1;
	glUniform4fv(GetUniformLocation(name), Count, value_ptr(value));
}

void ShaderProgram::SetMatrixUniform(const string& name, const mat3& value)
{
	ShowUseWarning();

	const int Count = 1;
	const bool Transpose = false;

	glUniformMatrix3fv(GetUniformLocation(name), Count, Transpose, value_ptr(value));
}

void ShaderProgram::SetMatrixUniform(const string& name, const mat4& value)
{
	ShowUseWarning();

	const int Count = 1;
	const bool Transpose = false;

	glUniformMatrix4fv(GetUniformLocation(name), Count, Transpose, value_ptr(value));
}

Uint32 ShaderProgram::GetUniformLocation(const string& name)
{
	Uint32 location = -1;
	try
	{
		location = uniformLocations.at(name);
	}
	catch (std::out_of_range)
	{
		throwFS((string)"Could not find stored uniform location with name: " + name + (string)". Created new map entry.\n");
	}

	return location;
}

Uint32 ShaderProgram::GetUniformLocationFromGl(const string& name) const
{
	return glGetUniformLocation(shaderProgramId, name.c_str());
}

void ShaderProgram::ShowUseWarning() const
{
	if (!isUsing)
		printFS("Warning: Use() has not been called on this shader");
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
