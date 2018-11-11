#include "../Header/ClickLabelManager.h"

void ClickLabelManager::Start()
{
	GetParameterCollection()->SetParameter(DoDraw, false);
}

string ClickLabelManager::GetGameObjectType() const
{
	return "ClickLabelManager";
}
