#include "../Header/ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
	shaderProgramId = glCreateProgram();
	CompileShaders();
}

void ShaderProgram::CompileShaders()
{
	setUse = false;
	CreateShaderProgram();
	MapUniformValues();

	Use();
	SetVec3("material.specularColor", vec3(1, 1, 1));
	SetFloat("material.shininessModifier", 1);
}

void ShaderProgram::MapUniformValues()
{
	uniformLocations["model"] = GetUniformLocationFromGl("model");
	uniformLocations["view"] = GetUniformLocationFromGl("view");
	uniformLocations["projection"] = GetUniformLocationFromGl("projection");
	uniformLocations["renderPerspective"] = GetUniformLocationFromGl("renderPerspective");

	uniformLocations["viewPosition"] = GetUniformLocationFromGl("viewPosition");
	uniformLocations["material.specularColor"] = GetUniformLocationFromGl("material.specularColor");
	uniformLocations["material.shininessModifier"] = GetUniformLocationFromGl("material.shininessModifier");
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

	return CreateShaderFromFilepath(GL_VERTEX_SHADER, "Resource/Shader/VertexShader.vshader", vertexShaderFallbackSource);
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

	return CreateShaderFromFilepath(GL_FRAGMENT_SHADER, "Resource/Shader/FragmentMaterialShader.fshader", fragmentShaderFallbackSource);
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
	setUse = true;
	glUseProgram(shaderProgramId);
}

void ShaderProgram::SetBool(const char* name, bool value)
{
	ShowUseWarning();

	if (name == "renderPerspective")
		renderPerspective = value;

	glUniform1i(GetUniformLocation(name), (int)value);
}

void ShaderProgram::SetInt(const char* name, int value)
{
	ShowUseWarning();
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetFloat(const char* name, float value)
{
	ShowUseWarning();
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetVec3(const char* name, const vec3& value)
{
	ShowUseWarning();

	const int Count = 1;
	glUniform3fv(GetUniformLocation(name), Count, value_ptr(value));
}

void ShaderProgram::SetMatrix(const char* name, const mat4& value)
{
	ShowUseWarning();

	const int Count = 1;
	const bool Transpose = false;

	glUniformMatrix4fv(GetUniformLocation(name), Count, Transpose, value_ptr(value));
}

void ShaderProgram::SetRenderPerspective(bool renderPerspective)
{
	ShowUseWarning();
	this->renderPerspective = renderPerspective;
}

bool ShaderProgram::RenderPerspective() const
{
	return renderPerspective;
}

Uint32 ShaderProgram::GetUniformLocation(const char* name) const
{
	Uint32 location = -1;
	try
	{
		location = uniformLocations.at(name);
	}
	catch (std::out_of_range)
	{
		location = GetUniformLocationFromGl(name);
		printf("Warning: Could not find stored uniform location with name: %s. Using GetUniformLocationFromGl().\n", name);
	}

	return location;
}

Uint32 ShaderProgram::GetUniformLocationFromGl(const char* name) const
{
	return glGetUniformLocation(shaderProgramId, name);
}

void ShaderProgram::ShowUseWarning() const
{
	if (!setUse)
		printf("Warning: Use() has not been called on this shader\n");
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
