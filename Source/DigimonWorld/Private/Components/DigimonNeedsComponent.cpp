// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DigimonNeedsComponent.h"

#include "Characters/PartnerDigimonCharacter.h"
#include "Components/DigimonLifeComponent.h"
#include "Data/DigimonBaseData.h"
#include "Data/DigimonGlobalData.h"
#include "Subsystems/DigimonTimeSubsystem.h"
#include "Utilities/DigimonSubsystems.h"

// Sets default values for this component's properties
UDigimonNeedsComponent::UDigimonNeedsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDigimonNeedsComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDigimonNeedsComponent::CheckPoopTime()
{
	if (!DigimonOwner || bNeedToPoop)
		return;

	TimeSinceLastPoop++;
	if (TimeSinceLastPoop >= PoopInterval)
	{
		TriggerPoopTimer();
	}
}

void UDigimonNeedsComponent::TriggerPoopTimer()
{;
	bNeedToPoop = true;
	if (UDigimonLifeComponent* LifeComponent = DigimonOwner->GetDigimonLifeComponent())
	{
		TimeForToilet = 12.0f + 0.6f * LifeComponent->GetDiscipline();
	}
	OnToiletNeedTriggered.Broadcast();
}

void UDigimonNeedsComponent::ToiletTimeOut()
{
	TriggerPoop(true);
}

void UDigimonNeedsComponent::TriggerPoop(bool bIsVisible)
{
	ResetToiletTimers();
	int32 ReduceWeight = PoopSize * 0.25f + FMath::RandRange(0, 3);

	if (!bIsVisible)
	{
		OnToiletUsed.Broadcast(ReduceWeight);
	}
	else
	{
		// display mesh
		OnToiletTimeout.Broadcast(ReduceWeight);
	}
}

void UDigimonNeedsComponent::UseToilet(int32& OutReduceWeight)
{
	if (!bNeedToPoop)
		return;
	
	OutReduceWeight = PoopSize * 0.25f + FMath::RandRange(0, 3);
	ResetToiletTimers();
	// TriggerPoop(false);
}

void UDigimonNeedsComponent::OnHourChanged(int32 NewHour)
{
	Energy -= FatigueRate;
	if (HungryHours.Contains(NewHour))
	{
		bIsHungry = true;
		OnHungerNeedsTriggered.Broadcast();
	}
}

void UDigimonNeedsComponent::OnMinuteChanged(int32 NewHour, int32 NewMinute)
{
	CheckPoopTime();
	if (bNeedToPoop)
	{
		TimeSinceToiletNeed++;

		if (TimeSinceToiletNeed > TimeForToilet)
		{
			ToiletTimeOut();
		}
	}
	if (bIsHungry)
	{
		TimeSinceHungry++;

		if (TimeSinceHungry > MaxTimeToFeed)
		{
			OnHungerTimeout.Broadcast(Energy < HungerThreshold);
			ResetHungerTimers();
		}
	}
}


// Called every frame
void UDigimonNeedsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDigimonNeedsComponent::InitializeDigimonNeeds(const FDigimonPartnerData& PartnerData,
                                                    const UDigimonGlobalsData* GlobalsData)
{
	HungerThreshold = PartnerData.HungerThreshold;
	FatigueRate = PartnerData.FatigueRate;
	DigimonActiveTime = PartnerData.DigimonActiveTime;
	MaxEnergy = PartnerData.MaxEnergy;
	Energy = MaxEnergy;
	PoopSize = PartnerData.PoopSize;
	HungryHours = PartnerData.HungryHours;
	if (!GetOwner())
		return;
	DigimonOwner = Cast<APartnerDigimonCharacter>(GetOwner());
	if (!DigimonOwner)
		return;

	TimeSinceLastPoop = 0;
	TimeForToilet = 0.0f;
	if (auto* TimeSystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		TimeSystem->OnHourChanged.AddDynamic(this, &UDigimonNeedsComponent::OnHourChanged);
		TimeSystem->OnMinuteChanged.AddDynamic(this, &UDigimonNeedsComponent::OnMinuteChanged);
	}
	if (!GlobalsData || !GlobalsData->ActiveHours.Contains(DigimonActiveTime))
		return;
	DigimonActivePeriod = GlobalsData->ActiveHours[DigimonActiveTime];
	if (!GlobalsData->PoopHours.Contains(DigimonOwner->GetDigimonStage()))
		return;

	PoopInterval = GlobalsData->PoopHours[DigimonOwner->GetDigimonStage()] * 60;
	MaxTimeToFeed = GlobalsData->MaxTimeToFeedDigimon;
}

bool UDigimonNeedsComponent::FeedDigimon(const int32 EnergyGain)
{
	Energy = FMath::Clamp(Energy + EnergyGain, 0, MaxEnergy);

	if (Energy >= HungerThreshold)
	{
		ResetHungerTimers();
		return true;
	}
	return false;
}

void UDigimonNeedsComponent::ResetToiletTimers()
{
	bNeedToPoop = false;
	TimeForToilet = 0.0f;
	TimeSinceLastPoop = 0;
	TimeSinceToiletNeed = 0.0f;
}

void UDigimonNeedsComponent::ResetHungerTimers()
{
	bIsHungry = false;
	TimeSinceHungry = 0.0f;
}
