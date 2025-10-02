// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Popup/StatsPopupWidget.h"

#include "Characters/PartnerDigimonCharacter.h"
#include "Components/DigimonStatsComponent.h"
#include "Subsystems/DigimonDataSubsystem.h"
#include "UI/Digimons/DigimonStatGainWidget.h"
#include "Utilities/DigimonSubsystems.h"

UDigimonStatsComponent* UStatsPopupWidget::GetDigimonStatsComp() const
{
	UDigimonDataSubsystem* DataSubsystem = UDigimonSubsystems::GetSubsystem<UDigimonDataSubsystem>(this);

	if (!DataSubsystem)
		return nullptr;

	APartnerDigimonCharacter* PartnerDigimon = DataSubsystem->GetDigimonCharacter();

	if (!PartnerDigimon)
		return nullptr;

	return PartnerDigimon->GetDigimonStatsComponent();
}

void UStatsPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StatWidgets = {
		{EDigimonStatType::Health, HealthStat},
		{EDigimonStatType::Mana, ManaStat},
		{EDigimonStatType::Strength, StrengthStat},
		{EDigimonStatType::Stamina, StaminaStat},
		{EDigimonStatType::Wisdom, WisdomStat},
		{EDigimonStatType::Speed, SpeedStat}
	};
}

void UStatsPopupWidget::InitializeStats()
{
	if (UDigimonStatsComponent* StatsComp = GetDigimonStatsComp())
	{
		const FDigimonStats DigimonStats = StatsComp->GetDigimonStats();
		const TMap<EDigimonStatType, int32> StatValues = {
			{EDigimonStatType::Health, DigimonStats.BaseHealth},
			{EDigimonStatType::Mana, DigimonStats.BaseMana},
			{EDigimonStatType::Strength, DigimonStats.BaseStrength},
			{EDigimonStatType::Stamina, DigimonStats.BaseStamina},
			{EDigimonStatType::Wisdom, DigimonStats.BaseWisdom},
			{EDigimonStatType::Speed, DigimonStats.BaseSpeed}
		};

		for (const auto& [StatType, Widget] : StatWidgets)
		{
			if (Widget)
			{
				Widget->SetStatAndGain(StatValues[StatType], 1);
			}
		}
	}
}
