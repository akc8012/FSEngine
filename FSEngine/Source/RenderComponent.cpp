#include "../Header/RenderComponent.h"

RenderComponent::RenderComponent(std::vector<float> vertices, std::vector<Uint32> indices, Uint32 stride)
{
	this->vertices = vertices;
	this->indices = indices;

	triangleCount = (Uint32)vertices.size() / stride;
	CreateVertexArray(stride);
}

void RenderComponent::CreateVertexArray(Uint32 stride)
{
	Uint32 vertexBufferId, elementBufferId;
	const int Amount = 1;
	glGenVertexArrays(Amount, &vertexArrayId);
	glGenBuffers(Amount, &vertexBufferId);
	glGenBuffers(Amount, &elementBufferId);

	glBindVertexArray(vertexArrayId);

	SendVertices(vertexBufferId, stride);
	SendIndices(elementBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(Amount, &elementBufferId);
	glDeleteBuffers(Amount, &vertexBufferId);
}

void RenderComponent::SendVertices(Uint32 vertexBufferId, Uint32 stride)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

	SendPositionAttribute(stride);
	SendTextureAttribute(stride);
}

void RenderComponent::SendPositionAttribute(Uint32 stride)
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.stride = stride;
	positionAttribute.offset = 0;

	SendVertexAttribute(positionAttribute);
}

void RenderComponent::SendTextureAttribute(Uint32 stride)
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 1;
	textureAttribute.size = 2;
	textureAttribute.stride = stride;
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Uint32), &indices.front(), GL_STATIC_DRAW);
}

void RenderComponent::BindVertexArray()
{
	glBindVertexArray(vertexArrayId);
}

Uint32 RenderComponent::GetTriangleCount() const
{
	return triangleCount;
}

RenderComponent::~RenderComponent()
{
	const int Amount = 1;
	glDeleteVertexArrays(Amount, &vertexArrayId);
}
