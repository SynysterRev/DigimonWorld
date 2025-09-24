// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/EnemyDigimonCharacter.h"

#include "Components/DigimonStatsComponent.h"
#include "Subsystems/DigimonDataSubsystem.h"

void AEnemyDigimonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyDigimonCharacter::InitializeDigimon(const FName& InDigimonID, UDigimonDataSubsystem* DataSubsystem)
{
	Super::InitializeDigimon(InDigimonID, DataSubsystem);
	FDigimonEnemyData EnemyData;
	if (DataSubsystem->GetEnemyDigimonStats(DigimonID, EnemyData))
	{
		InitializeBaseData(EnemyData.DigimonBaseData);
	}
}
