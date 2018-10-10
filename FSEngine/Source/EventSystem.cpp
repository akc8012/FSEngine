#include "../Header/EventSystem.h"

void EventSystem::AddListener(IEventListener* listener)
{
	listeners.push_back(listener);
}

void EventSystem::SendEvent(const string& name, const json& event)
{
	for (auto& listener : listeners)
		listener->ReceiveEvent(name, event);
}
