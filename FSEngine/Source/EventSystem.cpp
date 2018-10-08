#include "../Header/EventSystem.h"

void EventSystem::AddEvent(const json& event)
{
	events.push_back(event);
}

void EventSystem::ClearEvents()
{
	events.clear();
}
