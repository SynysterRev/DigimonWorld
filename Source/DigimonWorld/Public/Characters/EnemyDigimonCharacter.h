// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DigimonCharacter.h"
#include "EnemyDigimonCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API AEnemyDigimonCharacter : public ADigimonCharacter
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void InitializeDigimon(const FName& InDigimonID, UDigimonDataSubsystem* DataSubsystem) override;
};
