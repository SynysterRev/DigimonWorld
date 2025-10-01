// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/BaseInteractableActor.h"
#include "DigimonTrainingActor.generated.h"

enum class EDigimonStatType : uint8;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API ADigimonTrainingActor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:

	ADigimonTrainingActor();

protected:

	virtual void OnInteracted_Implementation(AActor* Interactor) override;

	UPROPERTY(EditAnywhere, Category="Stats")
	EDigimonStatType MainStatToTrain;

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 MainStatBaseValue;

	UPROPERTY(EditAnywhere, Category="Stats")
	EDigimonStatType SecondaryStatToTrain;

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 SecondaryStatBaseValue;

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 NumberHoursToSkip = 1;
};
