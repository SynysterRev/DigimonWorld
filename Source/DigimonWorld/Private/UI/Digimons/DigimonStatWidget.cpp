// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonStatWidget.h"

#include "CommonTextBlock.h"

void UDigimonStatWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (StatName && !StatText.IsEmpty())
	{
		StatName->SetText(StatText);
	}
}

void UDigimonStatWidget::SetStatValue(int32 InStatValue) const
{
	if (StatValue)
	{
		StatValue->SetText(FText::AsNumber(InStatValue));
	}
}

void UDigimonStatWidget::SetStatName(const FText& InStatName) const
{
	if (StatName)
	{
		StatName->SetText(InStatName);
	}
}
