// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/DigimonStatusStatsWidget.h"

#include "CommonTextBlock.h"
#include "Components/DigimonStatsComponent.h"

void UDigimonStatusStatsWidget::InitializeStats(UDigimonStatsComponent* StatsComponent) const
{
	if (!StatsComponent)
		return;

	if (StrengthValue)
	{
		StrengthValue->SetText(FText::FromString(FString::FromInt(StatsComponent->DigimonStats.BaseAttack)));
	}

	if (StaminaValue)
	{
		StaminaValue->SetText(FText::FromString(FString::FromInt(StatsComponent->DigimonStats.BaseDefense)));
	}

	if (WisdomValue)
	{
		WisdomValue->SetText(FText::FromString(FString::FromInt(StatsComponent->DigimonStats.BaseBrain)));
	}

	if (SpeedValue)
	{
		SpeedValue->SetText(FText::FromString(FString::FromInt(StatsComponent->DigimonStats.BaseSpeed)));
	}
}
