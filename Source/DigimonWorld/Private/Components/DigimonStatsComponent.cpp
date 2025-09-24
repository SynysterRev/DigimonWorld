// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DigimonStatsComponent.h"

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

void UDigimonStatsComponent::RestoreHealth(int32 HealthAmount)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + HealthAmount, 0, DigimonStats.BaseHealth);
}

void UDigimonStatsComponent::RestoreMana(int32 ManaAmount)
{
	CurrentMana = FMath::Clamp(CurrentMana + ManaAmount, 0, DigimonStats.BaseMana);
}

