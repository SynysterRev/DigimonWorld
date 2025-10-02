// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DigimonStatsComponent.h"

DEFINE_LOG_CATEGORY(LogStatsComponent);

// Sets default values for this component's properties
UDigimonStatsComponent::UDigimonStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDigimonStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDigimonStatsComponent::InitializeStats(const FDigimonStats& InBaseStats)
{
	DigimonStats = InBaseStats;
	CurrentHealth = DigimonStats.BaseHealth;
	CurrentMana = DigimonStats.BaseMana;
}

void UDigimonStatsComponent::ModifyStat(EDigimonStatType Stat, float Amount)
{
	switch (Stat)
	{
	case EDigimonStatType::Health:
		DigimonStats.BaseHealth = FMath::Clamp(
			DigimonStats.BaseHealth + Amount, 0, MAX_HEALTH_MANA);
		break;

	case EDigimonStatType::Mana:
		DigimonStats.BaseMana = FMath::Clamp(
			DigimonStats.BaseMana + Amount, 0, MAX_HEALTH_MANA);
		break;

	case EDigimonStatType::Strength:
		DigimonStats.BaseStrength = FMath::Clamp(
			DigimonStats.BaseStrength + Amount, 0, MAX_OTHERS_STATS);
		break;

	case EDigimonStatType::Stamina:
		DigimonStats.BaseStamina = FMath::Clamp(
			DigimonStats.BaseStamina + Amount, 0, MAX_OTHERS_STATS);
		break;

	case EDigimonStatType::Speed:
		DigimonStats.BaseSpeed = FMath::Clamp(
			DigimonStats.BaseSpeed + Amount, 0, MAX_OTHERS_STATS);
		break;

	case EDigimonStatType::Wisdom:
		DigimonStats.BaseWisdom = FMath::Clamp(
			DigimonStats.BaseWisdom + Amount, 0, MAX_OTHERS_STATS);
		break;

	default:
		UE_LOG(LogStatsComponent, Warning, TEXT("Unknown stat type in IncreaseBaseStat"));
		break;
	}
}

void UDigimonStatsComponent::RestoreHealth(int32 HealthAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0, DigimonStats.BaseHealth);
}

void UDigimonStatsComponent::RestoreMana(int32 ManaAmount)
{
	CurrentMana = FMath::Clamp(CurrentMana + ManaAmount, 0, DigimonStats.BaseMana);
}

