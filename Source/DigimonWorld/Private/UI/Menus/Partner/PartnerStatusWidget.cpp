// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Partner/PartnerStatusWidget.h"

#include "DigimonUtility.h"
#include "Characters/PartnerDigimonCharacter.h"
#include "Components/DigimonLifeComponent.h"
#include "Components/DigimonNeedsComponent.h"
#include "Components/DigimonStatsComponent.h"
#include "Subsystems/DigimonDataSubsystem.h"
#include "UI/CommonWidgets/BaseInfoWidget.h"
#include "UI/CommonWidgets/DigimonStatusGaugesWidget.h"
#include "UI/CommonWidgets/DigimonStatusStatsWidget.h"


void UPartnerStatusWidget::InitializeStats() const
{
	UDigimonStatsComponent* StatsComponent = CurrentDigimon->GetDigimonStatsComponent();

	if (!StatsComponent)
		return;

	if (HealthPoints)
	{
		int32 MaxHealth = StatsComponent->DigimonStats.BaseHealth;
		int32 CurrentHealth = StatsComponent->CurrentHealth;
		FText HealthPointsText = FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentHealth, MaxHealth));
		HealthPoints->SetValue(HealthPointsText);
	}

	if (ManaPoints)
	{
		int32 MaxMana = StatsComponent->DigimonStats.BaseMana;
		int32 CurrentMana = StatsComponent->CurrentMana;
		FText ManaPointsText = FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentMana, MaxMana));
		ManaPoints->SetValue(ManaPointsText);
	}

	if (StatsWidget)
	{
		StatsWidget->InitializeStats(StatsComponent);
	}
}

void UPartnerStatusWidget::InitializeInfo() const
{
	if (Type)
	{
		Type->SetValue(CurrentDigimon->GetDisplayName());
	}

	if (Stage)
	{
		FText DigimonStage = FDigimonUtility::GetTextForDigimonStage(CurrentDigimon->GetDigimonStage());
		Stage->SetValue(DigimonStage);
	}

	UDigimonLifeComponent* LifeComponent = CurrentDigimon->GetDigimonLifeComponent();

	if (!LifeComponent)
		return;

	if (Age)
	{
		Age->SetValue(FText::FromString(FString::FromInt(LifeComponent->GetAge())));
	}

	if (Weight)
	{
		Weight->SetValue(FText::FromString(FString::FromInt(LifeComponent->GetWeight())));
	}

	if (Attribute)
	{
		FText DigimonAttribute = FDigimonUtility::GetTextForDigimonAttribute(CurrentDigimon->GetDigimonAttribute());
		Attribute->SetValue(DigimonAttribute);
	}

	if (GaugesWidget)
	{
		GaugesWidget->InitializeGauges(LifeComponent);
	}

	UDigimonNeedsComponent* NeedsComponent = CurrentDigimon->GetDigimonNeedsComponent();

	if (!NeedsComponent)
		return;

	if (ActivePeriod)
	{
		int32 StartHour = NeedsComponent->GetDigimonActivePeriod().StartHour;
		int32 EndHour = NeedsComponent->GetDigimonActivePeriod().EndHour;
		FText ActivePeriodText = FText::FromString(FString::Printf(TEXT("%02d:00-%02d:00"), StartHour, EndHour));
		ActivePeriod->SetValue(ActivePeriodText);
	}
}

void UPartnerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
		return;

	UDigimonDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UDigimonDataSubsystem>();

	if (!DataSubsystem)
		return;

	CurrentDigimon = DataSubsystem->GetDigimonCharacter();

	if (!CurrentDigimon)
		return;

	InitializeInfo();
	InitializeStats();
}
