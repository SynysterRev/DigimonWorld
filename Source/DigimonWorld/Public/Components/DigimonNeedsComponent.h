// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/DigimonGlobalData.h"
#include "DigimonNeedsComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDigimonNeedsComponent, Log, All);

class APartnerDigimonCharacter;
struct FDigimonPartnerData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToiletTimeTriggered);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToiletTimeOver, int32, ReduceWeight);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHungerTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHungerTimeOver, bool, bIsBelowThreshold);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIGIMONWORLD_API UDigimonNeedsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDigimonNeedsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void CheckPoopTime();
	void TriggerPoopTimer();
	void ToiletTimeOut();

	UFUNCTION()
	void OnHourChanged(int32 NewHour);

	UFUNCTION()
	void OnMinuteChanged(int32 NewHour, int32 NewMinute);

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 HungerThreshold;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	TArray<int32> HungryHours;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 FatigueRate;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 MaxEnergy;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 Energy;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	int32 PoopSize;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	EDigimonActiveTime DigimonActiveTime;

	UPROPERTY(BlueprintReadWrite, Category="Life")
	FDigimonActivePeriod DigimonActivePeriod;

	UPROPERTY(BlueprintReadWrite, Category="Digimon")
	APartnerDigimonCharacter* DigimonOwner = nullptr;

	// Converted in minutes
	int32 PoopInterval = 0;
	bool bNeedToPoop = false;
	int32 TimeSinceLastPoop = 0;
	int32 TimeSinceToiletNeed = 0;
	float TimeForToilet = .0f;

	bool bIsHungry = false;
	int32 MaxTimeToFeed = 0;
	int32 TimeSinceHungry = 0;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeDigimonNeeds(const FDigimonPartnerData& PartnerData, const UDigimonGlobalsData* GlobalsData);

	bool GetNeedToPoop() const { return bNeedToPoop; }
	void UseToilet(int32& OutReduceWeight);
	void TriggerPoop(bool bIsVisible);

	/**
	 * @param EnergyGain Energy restored by the food
	 * @return True if full, false otherwise
	 */
	bool FeedDigimon(const int32 EnergyGain);
	void ResetToiletTimers();

	void ResetHungerTimers();

	UPROPERTY(BlueprintAssignable)
	FToiletTimeTriggered OnToiletNeedTriggered;

	UPROPERTY(BlueprintAssignable)
	FToiletTimeOver OnToiletUsed;

	UPROPERTY(BlueprintAssignable)
	FToiletTimeOver OnToiletTimeout;

	UPROPERTY(BlueprintAssignable)
	FHungerTime OnHungerNeedsTriggered;

	UPROPERTY(BlueprintAssignable)
	FHungerTimeOver OnHungerTimeout;
};
