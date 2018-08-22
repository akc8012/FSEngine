#include "../Header/ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
	CompileShaders();
}

void ShaderProgram::CompileShaders()
{
	SetParameter(IsUsing, false);
	//SetParameter(RenderPerspective, true);
	//SetParameter(EnableDepthTest, true);

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

Uint32 ShaderProgram::CreateShaderFromFilepath(Uint32 type, const char* filepath, const char* fallbackSource)
{
	int shaderId = TryCompileShaderSource(type, FileSystem::LoadTextFromFile(filepath).c_str());
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
		throw (string)"Error linking program: " + infoLog;
	}
}

string ShaderProgram::GetShaderTypeText(Uint32 type)
{
	return (string)(type == GL_VERTEX_SHADER ? "vertex" : "fragment");
}

void ShaderProgram::Use()
{
	SetParameter(IsUsing, true);
	glUseProgram(shaderProgramId);
}

void ShaderProgram::SetBoolUniform(const char* name, bool value)
{
	ShowUseWarning();
	glUniform1i(GetUniformLocation(name), (int)value);
}

void ShaderProgram::SetIntUniform(const char* name, int value)
{
	ShowUseWarning();
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloatUniform(const char* name, float value)
{
	ShowUseWarning();
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetVectorUniform(const char* name, const vec3& value)
{
	ShowUseWarning();

	const int Count = 1;
	glUniform3fv(GetUniformLocation(name), Count, value_ptr(value));
}

void ShaderProgram::SetVectorUniform(const char* name, const vec4& value)
{
	ShowUseWarning();

	const int Count = 1;
	glUniform4fv(GetUniformLocation(name), Count, value_ptr(value));
}

void ShaderProgram::SetMatrixUniform(const char* name, const mat3& value)
{
	ShowUseWarning();

	const int Count = 1;
	const bool Transpose = false;

	glUniformMatrix3fv(GetUniformLocation(name), Count, Transpose, value_ptr(value));
}

void ShaderProgram::SetMatrixUniform(const char* name, const mat4& value)
{
	ShowUseWarning();

	const int Count = 1;
	const bool Transpose = false;

	glUniformMatrix4fv(GetUniformLocation(name), Count, Transpose, value_ptr(value));
}

Uint32 ShaderProgram::GetUniformLocation(const char* name)
{
	Uint32 location = -1;
	try
	{
		location = uniformLocations.at(name);
	}
	catch (std::out_of_range)
	{
		throw (string)"Could not find stored uniform location with name: " + name + (string)". Created new map entry.\n";
	}

	return location;
}

Uint32 ShaderProgram::GetUniformLocationFromGl(const char* name) const
{
	return glGetUniformLocation(shaderProgramId, name);
}

void ShaderProgram::ShowUseWarning() const
{
	if (!GetParameter(IsUsing))
		printf("Warning: Use() has not been called on this shader\n");
}

void ShaderProgram::SetParameter(Parameters parameter, bool value)
{
	parameters[parameter] = value;
}

bool ShaderProgram::GetParameter(Parameters parameter) const
{
	return parameters[parameter];
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
