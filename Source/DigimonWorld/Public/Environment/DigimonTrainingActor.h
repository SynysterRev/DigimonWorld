// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Environment/BaseInteractableActor.h"
#include "DigimonTrainingActor.generated.h"

class APartnerDigimonCharacter;
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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void IncreaseStats();

	UPROPERTY(EditAnywhere, Category="Stats")
	TMap<EDigimonStatType, int32> TrainedStats;

	UPROPERTY(EditAnywhere, Category="Stats")
	int32 NumberHoursToSkip = 1;

	UPROPERTY(Transient)
	APartnerDigimonCharacter* PartnerDigimon = nullptr;
};
