#include "../Header/EventSystem.h"

void EventSystem::AddListener(const string& key, IEventListener* listener)
{
	listeners.emplace(key, listener);
}

void EventSystem::RemoveListener(IEventListener* listener)
{
	auto it = listeners.begin();
	while (it != listeners.end())
	{
		if (it->second == listener)
			it = listeners.erase(it);
		else
			it++;
	}
}

void EventSystem::RemoveListener(const string& key, IEventListener* listener)
{
	auto listenersOnKey = listeners.equal_range(key);
	if (listenersOnKey.first == listenersOnKey.second)
		throwFS("Could not remove listener since match could not be found on key: " + key);

	for (auto it = listenersOnKey.first; it != listenersOnKey.second; it++)
	{
		if (it->second == listener)
		{
			listeners.erase(it);
			break;
		}
	}
}

void EventSystem::SendEvent(const string& key, const json& event, bool showListenerWarning)
{
	auto listenersOnKey = listeners.equal_range(key);
	if (listenersOnKey.first == listenersOnKey.second)
	{
		if (showListenerWarning)
			printFS("Warning: Event sent with this key has no listeners: " + key);

		return;
	}

	for (auto it = listenersOnKey.first; it != listenersOnKey.second; it++)
		it->second->ReceiveEvent(key, event);
}
