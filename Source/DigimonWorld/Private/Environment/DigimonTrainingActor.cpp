// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/DigimonTrainingActor.h"

#include "Characters/PartnerDigimonCharacter.h"
#include "Characters/TamerCharacter.h"
#include "Characters/TamerController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/DigimonTimeSubsystem.h"
#include "Subsystems/DigimonUISubsystem.h"
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

	PartnerDigimon = TamerCharacter->GetPartnerDigimon();

	if (!PartnerDigimon)
		return;

	if (ATamerController* PC = Cast<ATamerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PC->EnableCharacterInput(false);
	}

	if (UDigimonUISubsystem* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		UISubsystem->ShowStatsPopup(TrainedStats);
		UISubsystem->OnStatsAnimationEnd.AddDynamic(this, &ADigimonTrainingActor::IncreaseStats);
	}
}

void ADigimonTrainingActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UDigimonUISubsystem* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		UISubsystem->OnStatsAnimationEnd.RemoveDynamic(this, &ADigimonTrainingActor::IncreaseStats);
	}
	Super::EndPlay(EndPlayReason);
}

void ADigimonTrainingActor::IncreaseStats()
{
	if (PartnerDigimon)
	{
		for (const auto& [StatType, Value] : TrainedStats)
		{
			PartnerDigimon->IncreaseBaseStat(StatType, Value);
		}
	}

	if (ATamerController* PC = Cast<ATamerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PC->EnableCharacterInput(true);
	}

	if (UDigimonUISubsystem* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		UISubsystem->OnStatsAnimationEnd.RemoveDynamic(this, &ADigimonTrainingActor::IncreaseStats);
	}

	if (UDigimonTimeSubsystem* TimeSubsystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		TimeSubsystem->SkipTime(NumberHoursToSkip);
	}
}
