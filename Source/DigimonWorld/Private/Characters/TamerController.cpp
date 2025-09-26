// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TamerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Subsystems/DigimonMenuSubsystem.h"

void ATamerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (CharacterMappingContext)
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}

		if (MenuMappingContext)
		{
			Subsystem->AddMappingContext(MenuMappingContext, 1);
		}
	}
}

void ATamerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Started, this, &ATamerController::OpenPauseMenu);
	}
}

void ATamerController::EnableCharacterInput(bool bEnable) const
{
	if (!CharacterMappingContext)
		return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bEnable)
		{
			Subsystem->AddMappingContext(CharacterMappingContext, 0);
		}
		else
		{
			Subsystem->RemoveMappingContext(CharacterMappingContext);
		}
	}
}

void ATamerController::EnableMenuInput(bool bEnable) const
{
	if (!MenuMappingContext)
		return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (bEnable)
		{
			Subsystem->AddMappingContext(MenuMappingContext, 1);
		}
		else
		{
			Subsystem->RemoveMappingContext(MenuMappingContext);
		}
	}
}

void ATamerController::OpenPauseMenu(const FInputActionValue& Value)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UDigimonMenuSubsystem* MenuSubsystem = GameInstance->GetSubsystem<UDigimonMenuSubsystem>())
		{
			MenuSubsystem->OpenPauseMenu();
		}
	}
}
