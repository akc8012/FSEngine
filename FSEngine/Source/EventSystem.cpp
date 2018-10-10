#include "../Header/EventSystem.h"

void EventSystem::AddListener(IEventListener* listener)
{
	listeners.push_back(listener);
}

void EventSystem::SendEvent(const json& event)
{
	for (auto& listener : listeners)
		listener->ReceiveEvent(event);
}

void EventSystem::AddEvent(const json& event)
{
	events.push_back(event);
}

json EventSystem::ReadEvent()
{
	json event = events.back();

	ClearEvents();

	return event;
}

void EventSystem::ClearEvents()
{
	events.clear();
}
