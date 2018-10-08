#include "../Header/EventSystem.h"

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
