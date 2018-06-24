#include "../Header/RenderComponent.h"

RenderComponent::RenderComponent(float* vertices, Uint32* indices, const char* textureFilepath)
{
	this->vertices = vertices;
	this->indices = indices;

	CreateVertexArray();
	texture = new Texture(textureFilepath);
}

void RenderComponent::CreateVertexArray()
{
	Uint32 vertexBufferId, elementBufferId;
	const int Amount = 1;
	glGenVertexArrays(Amount, &vertexArrayId);
	glGenBuffers(Amount, &vertexBufferId);
	glGenBuffers(Amount, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	SendVertices(vertexBufferId);
	SendIndices(elementBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(Amount, &elementBufferId);
	glDeleteBuffers(Amount, &vertexBufferId);
}

void RenderComponent::SendVertices(Uint32 vertexBufferId)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	SendPositionAttribute();
	SendTextureAttribute();
}

void RenderComponent::SendPositionAttribute()
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.stride = 5;
	positionAttribute.offset = 0;

	SendVertexAttribute(positionAttribute);
}

void RenderComponent::SendTextureAttribute()
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 1;
	textureAttribute.size = 2;
	textureAttribute.stride = 5;
	textureAttribute.offset = 3;

	SendVertexAttribute(textureAttribute);
}

void RenderComponent::SendVertexAttribute(const VertexAttribute& attribute)
{
	glVertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, attribute.normalize, attribute.stride * sizeof(float), (void*)(attribute.offset * sizeof(float)));
	glEnableVertexAttribArray(attribute.location);
}

void RenderComponent::SendIndices(Uint32 elementBufferId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

RenderComponent::~RenderComponent()
{
	delete texture;

	const int Amount = 1;
	glDeleteVertexArrays(Amount, &vertexArrayId);
}
