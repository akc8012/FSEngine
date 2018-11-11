#include "../Header/GameObjectFactory.h"

namespace GameObjectFactory
{
	unique_ptr<GameObject> MakeGameObject(const string& type)
	{
		if (type == "CubePrimitive")
			return make_unique<CubePrimitive>();

		else if (type == "QuadPrimitive")
			return make_unique<QuadPrimitive>();

		else if (type == "Camera")
			return make_unique<Camera>();

		else if (type == "PlayerShip")
			return make_unique<PlayerShip>();

		else if (type == "RenderText")
			return make_unique<RenderText>();

		else if (type == "ClickLabel")
			return make_unique<ClickLabel>();

		else if (type == "ClickLabelManager")
			return make_unique<ClickLabelManager>();

		throwFS("Cannot make GameObject of unrecognized type: " + type);
	}
}
