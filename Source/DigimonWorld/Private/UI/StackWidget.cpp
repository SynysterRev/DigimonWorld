// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StackWidget.h"

void UStackWidget::PopWidget(UCommonActivatableWidget* ActivatableWidget) const
{
	if (!Stack || ! ActivatableWidget)
		return;
	
	Stack->RemoveWidget(*ActivatableWidget);
}

void UStackWidget::PopLastWidget() const
{
	if (!Stack)
		return;
	
	if (UCommonActivatableWidget* ActiveWidget = Stack->GetActiveWidget())
	{
		Stack->RemoveWidget(*ActiveWidget);
	}
}

void UStackWidget::PopAllWidget() const
{
	if (Stack)
	{
		Stack->ClearWidgets();
	}
}

UCommonActivatableWidget* UStackWidget::GetActiveWidget() const
{
	if (Stack)
	{
		return Stack->GetActiveWidget();
	}
	return nullptr;
}

int32 UStackWidget::GetTotalActiveWidgets() const
{
	return Stack->GetNumWidgets();
}
