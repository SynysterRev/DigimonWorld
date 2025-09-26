// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MenuStack.h"

void UMenuStack::PushWidget(UCommonActivatableWidget* ActivatableWidget) const
{
	if (!MenuStack || !ActivatableWidget)
		return;
	
	MenuStack->AddWidgetInstance(*ActivatableWidget);
}

void UMenuStack::PopWidget(UCommonActivatableWidget* ActivatableWidget) const
{
	if (!MenuStack || ! ActivatableWidget)
		return;
	
	MenuStack->RemoveWidget(*ActivatableWidget);
}

void UMenuStack::PopLastWidget() const
{
	if (!MenuStack)
		return;
	
	if (UCommonActivatableWidget* ActiveWidget = MenuStack->GetActiveWidget())
	{
		MenuStack->RemoveWidget(*ActiveWidget);
	}
}
