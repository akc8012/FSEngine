#include "..\Header\MeshComponent.h"

MeshComponent::MeshComponent(const vector<Vertex>& vertices, const vector<Uint32>& indices)
{
	this->vertices = vertices;
	this->indices = indices;

	CreateVertexArray();
}

void MeshComponent::CreateVertexArray()
{
	Uint32 vertexBufferId, elementBufferId;
	const int Amount = 1;
	glGenVertexArrays(Amount, &vertexArrayId);
	glGenBuffers(Amount, &vertexBufferId);
	glGenBuffers(Amount, &elementBufferId);

	BindVertexArray();

	SendVertices(vertexBufferId);
	SendIndices(elementBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, NULL);
	glBindVertexArray(NULL);

	glDeleteBuffers(Amount, &elementBufferId);
	glDeleteBuffers(Amount, &vertexBufferId);
}

void MeshComponent::SendVertices(Uint32 vertexBufferId)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

	SendPositionAttribute();
	SendNormalAttribute();
	SendTextureAttribute();
}

void MeshComponent::SendPositionAttribute()
{
	VertexAttribute positionAttribute;
	positionAttribute.location = 0;
	positionAttribute.size = 3;
	positionAttribute.offset = 0;

	SendVertexAttribute(positionAttribute);
}

void MeshComponent::SendNormalAttribute()
{
	VertexAttribute normalAttribute;
	normalAttribute.location = 1;
	normalAttribute.size = 3;
	normalAttribute.offset = offsetof(Vertex, normal);

	SendVertexAttribute(normalAttribute);
}

void MeshComponent::SendTextureAttribute()
{
	VertexAttribute textureAttribute;
	textureAttribute.location = 2;
	textureAttribute.size = 2;
	textureAttribute.offset = offsetof(Vertex, textureCoord);

	SendVertexAttribute(textureAttribute);
}

void MeshComponent::SendVertexAttribute(const VertexAttribute& attribute)
{
	glVertexAttribPointer(attribute.location, attribute.size, GL_FLOAT, attribute.normalize, attribute.stride, (void*)attribute.offset);
	glEnableVertexAttribArray(attribute.location);
}

void MeshComponent::SendIndices(Uint32 elementBufferId)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Uint32), &indices.front(), GL_STATIC_DRAW);
}

void MeshComponent::BindVertexArray()
{
	glBindVertexArray(vertexArrayId);
}

const type_info& MeshComponent::GetType() const
{
	return typeid(this);
}
