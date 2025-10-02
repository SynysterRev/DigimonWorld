// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DigimonBaseData.h"
#include "DigimonStatsComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogStatsComponent, Log, All);

UCLASS(ClassGroup=(Custom),BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class DIGIMONWORLD_API UDigimonStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDigimonStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|Runtime")
	FDigimonStats DigimonStats;
	
public:
		
	void RestoreHealth(int32 HealthAmount);
	void RestoreMana(int32 ManaAmount);
	
	virtual void InitializeStats(const FDigimonStats& InBaseStats);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|Runtime")
	int32 CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stats|Runtime")
	int32 CurrentMana;

	UFUNCTION(BlueprintPure, Category="Stats")
	const FDigimonStats& GetDigimonStats() const { return DigimonStats; }

	UFUNCTION(BlueprintCallable, Category="Stats")
	void ModifyStat(EDigimonStatType Stat, float Amount);
};
