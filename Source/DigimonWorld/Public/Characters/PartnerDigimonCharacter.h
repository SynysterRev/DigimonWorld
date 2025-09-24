// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DigimonCharacter.h"
#include "PartnerDigimonCharacter.generated.h"

class UDigimonNeedsComponent;
enum class EDigimonStatType : uint8;
class UDigimonLifeComponent;
class UPartnerStatsComponent;

UCLASS()
class DIGIMONWORLD_API APartnerDigimonCharacter : public ADigimonCharacter
{
	GENERATED_BODY()

public:
	APartnerDigimonCharacter();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void InitializeDigimon(const FName& InDigimonID, UDigimonDataSubsystem* DataSubsystem) override;
	
	void AssignTamer(ATamerCharacter* Tamer);
	void TryConsumeItem();

	ATamerCharacter* GetTamerCharacter() const { return TamerOwner; }

	void IncreaseBaseStat(EDigimonStatType Stat, int32 Amount) const;

	FORCEINLINE UDigimonLifeComponent* GetDigimonLifeComponent() const { return LifeComponent; }
	FORCEINLINE UDigimonNeedsComponent* GetDigimonNeedsComponent() const { return NeedsComponent; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FavoriteFoodRefusalNotHungry = 0.05f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FoodRefusalWhenHungry = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float FoodRefusalNotHungry = 0.25f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ObjectRefusal = 0.2f;

	UPROPERTY()
	TObjectPtr<ATamerCharacter> TamerOwner = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDigimonLifeComponent> LifeComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDigimonNeedsComponent> NeedsComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Training")
	TMap<EDigimonStatType, int32> TrainingModifiers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Globals Data")
	TObjectPtr<UDigimonGlobalsData> Globals = nullptr;

	UFUNCTION()
	void OnToiletNeeded();

	UFUNCTION()
	void OnToiletUsed(int32 ReduceWeight);

	UFUNCTION()
	void OnToiletTimeout(int32 ReduceWeight);

	UFUNCTION()
	void OnHungerTriggered();

	UFUNCTION()
	void OnHungerTimeout(bool bIsEnergyBelowThreshold);
};
