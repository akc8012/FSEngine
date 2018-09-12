#pragma once

#include <glm\glm.hpp>
using glm::mat4;
using glm::vec4;
using glm::vec3;
using glm::vec2;

#include <string>
using std::string;

class FSDebug
{
public:
	static void Print(int message);
	static void Print(float message);
	static void Print(const mat4& message);
	static void Print(const vec4& message);
	static void Print(const vec3& message);
	static void Print(const vec2& message);
	static void Print(const string& message);
};

template<typename T> constexpr auto printFS(T message)
{
	return FSDebug::Print(message);
}

template<typename T> constexpr auto printcFS(T message)
{
	system("cls");
	return FSDebug::Print(message);
}
