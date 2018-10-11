#include "../Header/EventSystem.h"

void EventSystem::AddListener(const string& key, IEventListener* listener)
{
	listeners.emplace(key, listener);
}

void EventSystem::SendEvent(const string& key, const json& event)
{
	auto listenersOnKey = listeners.equal_range(key);
	if (listenersOnKey.first == listenersOnKey.second)
	{
		printFS("Warning: Event sent with key \"" + key + "\" has no listeners");
		return;
	}

	for (auto listener = listenersOnKey.first; listener != listenersOnKey.second; listener++)
		listener->second->ReceiveEvent(key, event);
}
