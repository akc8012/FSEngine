#include "../Header/Color.h"

Color::Color()
{
	color = vec4(0);
}

Color::Color(const vec3& color)
{
	SetColor(color);
}

Color::Color(float r, float g, float b)
{
	SetColor(vec3(r, g, b));
}

Color::Color(int r, int g, int b)
{
	SetColor(vec3((float)r, (float)g, (float)b));
}

void Color::SetColor(const vec3& color)
{
	SetColor(vec4(color, 1.0f));
}

void Color::SetColor(const vec4& color)
{
	this->color = color;
}

vec4 Color::GetColor() const
{
	return color;
}

json Color::GetJson() const
{
	json j = Shading::GetJson();
	j["Color"] = { color.r, color.g, color.b, color.a };

	return j;
}

void Color::SetFromJson(const json& j)
{
	Shading::SetFromJson(j);

	json color = j["Color"];
	SetColor(vec4(color[0], color[1], color[2], color[3]));
}

Types::ComponentType Color::GetComponentTypeId() const
{
	return ComponentTypeId;
}
