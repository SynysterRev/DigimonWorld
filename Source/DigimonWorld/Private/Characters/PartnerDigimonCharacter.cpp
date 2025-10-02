// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PartnerDigimonCharacter.h"

#include "Components/DigimonLifeComponent.h"
#include "Components/DigimonNeedsComponent.h"
#include "Components/DigimonStatsComponent.h"
#include "Subsystems/DigimonDataSubsystem.h"

APartnerDigimonCharacter::APartnerDigimonCharacter()
{
	LifeComponent = CreateDefaultSubobject<UDigimonLifeComponent>("Life Component");
	NeedsComponent = CreateDefaultSubobject<UDigimonNeedsComponent>("Needs Component");
}

void APartnerDigimonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APartnerDigimonCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (NeedsComponent)
	{
		NeedsComponent->OnToiletNeedTriggered.RemoveDynamic(this, &APartnerDigimonCharacter::OnToiletNeeded);
		// NeedsComponent->OnToiletUsed.RemoveDynamic(this, &APartnerDigimonCharacter::OnToiletUsed);
		NeedsComponent->OnToiletTimeout.RemoveDynamic(this, &APartnerDigimonCharacter::OnToiletTimeout);
		NeedsComponent->OnHungerNeedsTriggered.RemoveDynamic(this, &APartnerDigimonCharacter::OnHungerTriggered);
		NeedsComponent->OnHungerTimeout.RemoveDynamic(this, &APartnerDigimonCharacter::OnHungerTimeout);
	}
	Super::EndPlay(EndPlayReason);
}

void APartnerDigimonCharacter::InitializeDigimon(const FName& InDigimonID, UDigimonDataSubsystem* DataSubsystem)
{
	Super::InitializeDigimon(InDigimonID, DataSubsystem);
	if (!LifeComponent)
	{
		UE_LOG(LogDigimonCharacter, Error, TEXT("No life component created in the digimon"));
		return;
	}
	Globals = DataSubsystem->GetDigimonGlobalsData();
	FDigimonPartnerData PartnerData;
	if (DataSubsystem->GetPartnerDigimonStats(InDigimonID, PartnerData))
	{
		InitializeBaseData(PartnerData.DigimonBaseData);

		TrainingModifiers = PartnerData.TrainingModifiers;
		LifeComponent->InitializeDigimonLife(PartnerData);
		NeedsComponent->InitializeDigimonNeeds(PartnerData, Globals);
	}
	NeedsComponent->OnToiletNeedTriggered.AddDynamic(this, &APartnerDigimonCharacter::OnToiletNeeded);
	// NeedsComponent->OnToiletUsed.AddDynamic(this, &APartnerDigimonCharacter::OnToiletUsed);
	NeedsComponent->OnToiletTimeout.AddDynamic(this, &APartnerDigimonCharacter::OnToiletTimeout);
	NeedsComponent->OnHungerNeedsTriggered.AddDynamic(this, &APartnerDigimonCharacter::OnHungerTriggered);
	NeedsComponent->OnHungerTimeout.AddDynamic(this, &APartnerDigimonCharacter::OnHungerTimeout);
}

void APartnerDigimonCharacter::AssignTamer(ATamerCharacter* Tamer)
{
	if (Tamer != nullptr)
	{
		TamerOwner = Tamer;
	}
}

bool APartnerDigimonCharacter::NeedToUseToilet() const
{
	if (!NeedsComponent)
		return false;
	
	return NeedsComponent->GetNeedToPoop();
}

void APartnerDigimonCharacter::TryConsumeItem()
{
	if (!NeedsComponent)
		return;

	if (NeedsComponent->FeedDigimon(15))
	{
		RemoveBubbleIndicator(EDigimonBubbleType::Hungry);
	}
}

void APartnerDigimonCharacter::IncreaseBaseStat(EDigimonStatType Stat, int32 Amount) const
{
	if (!StatsComponent)
		return;
	
	StatsComponent->ModifyStat(Stat, Amount);
}

void APartnerDigimonCharacter::OnToiletNeeded()
{
	AddNewBubbleIndicator(EDigimonBubbleType::Toilet);
}

void APartnerDigimonCharacter::UseToilet()
{
	OnToiletUsedTrigger.Broadcast();
	int32 ReduceWeight = 1;
	if (NeedsComponent)
	{
		NeedsComponent->UseToilet(ReduceWeight);
	}
	if (LifeComponent)
	{
		LifeComponent->RemoveWeight(ReduceWeight);
	}
	RemoveBubbleIndicator(EDigimonBubbleType::Toilet);
}

void APartnerDigimonCharacter::OnToiletTimeout(int32 ReduceWeight)
{
	if (LifeComponent)
	{
		LifeComponent->AddCareMistakes(1);
		LifeComponent->AddVirusGauge();
		LifeComponent->RemoveHappiness(10);
		LifeComponent->RemoveDiscipline(5);
		LifeComponent->RemoveWeight(ReduceWeight);
	}
	RemoveBubbleIndicator(EDigimonBubbleType::Toilet);
}

void APartnerDigimonCharacter::OnHungerTriggered()
{
	AddNewBubbleIndicator(EDigimonBubbleType::Hungry);
}

void APartnerDigimonCharacter::OnHungerTimeout(bool bIsEnergyBelowThreshold)
{
	if (bIsEnergyBelowThreshold && LifeComponent)
	{
		LifeComponent->AddCareMistakes(1);
	}
	RemoveBubbleIndicator(EDigimonBubbleType::Hungry);
}
