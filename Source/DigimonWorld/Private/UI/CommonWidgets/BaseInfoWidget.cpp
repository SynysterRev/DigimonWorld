// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/BaseInfoWidget.h"

void UBaseInfoWidget::SetTitle(const FText& NewTitle) const
{
	if (Title)
	{
		Title->SetText(NewTitle);
	}
}

void UBaseInfoWidget::SetValue(const FText& NewValue) const
{
	if (Value)
	{
		Value->SetText(NewValue);
	}
}
