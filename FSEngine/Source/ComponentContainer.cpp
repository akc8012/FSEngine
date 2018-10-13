#include "../Header/ComponentContainer.h"

ComponentContainer::ComponentContainer()
{
	mesh = make_unique<ComponentCollection<Mesh>>();
	shading = make_unique<ComponentCollection<Shading>>();
	transform = make_unique<ComponentCollection<Transform>>();
}
