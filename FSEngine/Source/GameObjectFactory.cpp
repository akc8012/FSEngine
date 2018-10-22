#include "../Header/GameObjectFactory.h"

unique_ptr<GameObject> GameObjectFactory::MakeGameObject(const string& type)
{
	if (type == "CubePrimitive")
		return make_unique<CubePrimitive>();

	throwFS("Cannot make GameObject of unrecognized type: " + type);
}
