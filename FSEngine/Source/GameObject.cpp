#include "../Header/GameObject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	if (renderComponent == NULL)
		delete renderComponent;
}
