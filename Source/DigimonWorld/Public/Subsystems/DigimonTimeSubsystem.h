// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonTimeSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewDay, int32, NewDay);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHourChanged, int32, NewHour);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMinuteChanged, int32, NewHour, int32, NewMinute);

UCLASS()
class DIGIMONWORLD_API UDigimonTimeSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual TStatId GetStatId() const override;
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override { return bCanTick; }

	float GetCurrentTimeOfDay() const { return CurrentTimeOfDay; }
	int32 GetCurrentHourOfDay() const { return FMath::FloorToInt(CurrentTimeOfDay); }
	int32 GetCurrentDay() const { return CurrentDay; }

	// float GetTimeSince(float PreviousTime) const;

	UPROPERTY(BlueprintAssignable)
	FOnNewDay OnNewDay;

	UPROPERTY(BlueprintAssignable, Category = "Digimon Time")
	FOnHourChanged OnHourChanged;

	UPROPERTY(BlueprintAssignable, Category = "Digimon Time")
	FOnMinuteChanged OnMinuteChanged;

private:
	static constexpr float TIME_SCALE = 60.0f;

	float CurrentTimeOfDay = 5.99f;
	int32 CurrentDay = 1;
	int32 LastHour = 5;
	int32 LastMinute = 59;

	bool bCanTick = true;
};
