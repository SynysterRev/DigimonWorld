// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DigimonLifeComponent.h"

#include "Subsystems/DigimonTimeSubsystem.h"

const int32 MAX_VIRUS_BAR = 16;
const int32 MAX_DISICPLINE = 100;
const int32 MAX_HAPPINESS = 100;
const int32 MAX_WEIGHT = 999;

// Sets default values for this component's properties
UDigimonLifeComponent::UDigimonLifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDigimonLifeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDigimonLifeComponent::OnHourChanged(int32 NewHour)
{
}


void UDigimonLifeComponent::InitializeDigimonLife(const FDigimonPartnerData& PartnerData)
{
	MaxAge = PartnerData.MaxAge;
	Weight = PartnerData.Weight;
	
	if (!GetOwner())
	{
		return;
	}
	
	if (auto* TimeSystem = GetOwner()->GetGameInstance()->GetSubsystem<UDigimonTimeSubsystem>())
	{
		TimeSystem->OnHourChanged.AddDynamic(this, &UDigimonLifeComponent::OnHourChanged);
		BornHour = TimeSystem->GetCurrentHourOfDay();
	}
}

// Called every frame
void UDigimonLifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDigimonLifeComponent::AddCareMistakes(int32 Amount)
{
	CareMistakes += Amount;
}

void UDigimonLifeComponent::ResetCareMistakes()
{
	CareMistakes = 0;
}

void UDigimonLifeComponent::AddVirusGauge()
{
	VirusGauge += 1;
	if (VirusGauge == MAX_VIRUS_BAR)
	{
		// Sukamon Digivolution
		ResetVirusGauge();
	}
}

void UDigimonLifeComponent::ResetVirusGauge()
{
	VirusGauge = 0;
}

void UDigimonLifeComponent::AddDiscipline(int32 Amount)
{
	Discipline = FMath::Clamp(Discipline + Amount, 0, MAX_DISICPLINE);
}

void UDigimonLifeComponent::RemoveDiscipline(int32 Amount)
{
	Discipline = FMath::Clamp(Discipline - Amount, 0, MAX_DISICPLINE);
}

void UDigimonLifeComponent::SetDiscipline(int32 Amount)
{
	Discipline = FMath::Clamp(Amount, 0, MAX_DISICPLINE);
}

void UDigimonLifeComponent::AddHappiness(int32 Amount)
{
	Happiness = FMath::Clamp(Happiness + Amount, -MAX_HAPPINESS, MAX_HAPPINESS);
}

void UDigimonLifeComponent::RemoveHappiness(int32 Amount)
{
	Happiness = FMath::Clamp(Happiness - Amount, -MAX_HAPPINESS, MAX_HAPPINESS);
}

void UDigimonLifeComponent::SetHappiness(int32 Amount)
{
	Happiness = FMath::Clamp(Amount, -MAX_HAPPINESS, MAX_HAPPINESS);
}

void UDigimonLifeComponent::AddWeight(int32 Amount)
{
	Weight = FMath::Clamp(Weight + Amount, 0, MAX_WEIGHT);
}

void UDigimonLifeComponent::RemoveWeight(int32 Amount)
{
	Happiness = FMath::Clamp(Weight - Amount, 0, MAX_WEIGHT);
}

void UDigimonLifeComponent::SetWeight(int32 Amount)
{
	Happiness = FMath::Clamp(Amount, 0, MAX_WEIGHT);
}

