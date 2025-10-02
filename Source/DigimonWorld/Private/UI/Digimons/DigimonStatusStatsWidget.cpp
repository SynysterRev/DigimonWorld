// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonStatusStatsWidget.h"

#include "CommonTextBlock.h"
#include "Components/DigimonStatsComponent.h"
#include "UI/Digimons/DigimonStatWidget.h"

void UDigimonStatusStatsWidget::InitializeStats(UDigimonStatsComponent* StatsComponent) const
{
	if (!StatsComponent)
		return;

	const FDigimonStats DigimonStats = StatsComponent->GetDigimonStats();
	if (StrengthStat)
	{
		StrengthStat->SetStatValue(DigimonStats.BaseStrength);
	}

	if (StaminaStat)
	{
		StaminaStat->SetStatValue(DigimonStats.BaseStamina);
	}

	if (WisdomStat)
	{
		WisdomStat->SetStatValue(DigimonStats.BaseWisdom);
	}

	if (SpeedStat)
	{
		SpeedStat->SetStatValue(DigimonStats.BaseSpeed);
	}
}
