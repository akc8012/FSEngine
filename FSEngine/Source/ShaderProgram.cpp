#include "../Header/ShaderProgram.h"
#include "../Header/AndUtility.h"
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram()
{
	createShaderProgram();
}

void ShaderProgram::createShaderProgram()
{
	glDeleteProgram(shaderProgramId);
	shaderProgramId = glCreateProgram();

	unsigned int vertexShaderId = createVertexShader();
	glAttachShader(shaderProgramId, vertexShaderId);

	unsigned int fragmentShaderId = createFragmentShader();
	glAttachShader(shaderProgramId, fragmentShaderId);

	int success;
	glLinkProgram(shaderProgramId);
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		throw (string)"Error linking program: " + infoLog;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
}

unsigned int ShaderProgram::createVertexShader()
{
	char vertexShaderFallbackSource[] = {
		"#version 330 core\n"
		"layout (location = 0) in vec3 vertexPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(vertexPosition, 1.0);\n"
		"}\n"
	};

	return createShaderFromFilepath(GL_VERTEX_SHADER, "Resource/Shader/VertexShader.shader", vertexShaderFallbackSource);
}

unsigned int ShaderProgram::createFragmentShader()
{
	char fragmentShaderFallbackSource[] = {
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n"
	};

	return createShaderFromFilepath(GL_FRAGMENT_SHADER, "Resource/Shader/FragmentMixShader.shader", fragmentShaderFallbackSource);
}

unsigned int ShaderProgram::createShaderFromFilepath(unsigned int type, const char* filepath, const char* fallbackSource)
{
	int shaderId = tryCompileShaderSource(type, AndUtility::loadTextFromFile(filepath).c_str());
	if (shaderId == -1)
	{
		shaderId = tryCompileShaderSource(type, fallbackSource);
		cout << "Using fallback " << getShaderTypeText(type) << " shader" << endl;
	}

	return shaderId;
}

int ShaderProgram::tryCompileShaderSource(unsigned int type, const char* source)
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
		cout << (string)"Warning: Unable to compile " << getShaderTypeText(type) << " shader: " << infoLog;
		return -1;
	}

	return shaderId;
}

string ShaderProgram::getShaderTypeText(unsigned int type)
{
	return type == GL_VERTEX_SHADER ? (string)"vertex" : (string)"fragment";
}

unsigned int ShaderProgram::getId()
{
	return shaderProgramId;
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(shaderProgramId);
}
