// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/DigimonTrainingActor.h"

#include "Characters/PartnerDigimonCharacter.h"
#include "Characters/TamerCharacter.h"
#include "Components/BoxComponent.h"
#include "Subsystems/DigimonTimeSubsystem.h"
#include "Utilities/DigimonSubsystems.h"

ADigimonTrainingActor::ADigimonTrainingActor()
{
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	MeshComponent->SetupAttachment(Collider);
}

void ADigimonTrainingActor::OnInteracted_Implementation(AActor* Interactor)
{
	Super::OnInteracted_Implementation(Interactor);

	// need to add animation etc...
	// for now upgrade stats instantaneously

	ATamerCharacter* TamerCharacter = Cast<ATamerCharacter>(Interactor);
	if (!TamerCharacter)
		return;

	APartnerDigimonCharacter* PartnerDigimon = TamerCharacter->GetPartnerDigimon();

	if (!PartnerDigimon)
		return;

	PartnerDigimon->IncreaseBaseStat(MainStatToTrain, MainStatBaseValue);
	PartnerDigimon->IncreaseBaseStat(SecondaryStatToTrain, SecondaryStatBaseValue);

	if (UDigimonTimeSubsystem* TimeSubsystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		TimeSubsystem->SkipTime(NumberHoursToSkip);
	}
}
