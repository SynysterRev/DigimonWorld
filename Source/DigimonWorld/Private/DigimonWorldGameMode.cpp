// Copyright Epic Games, Inc. All Rights Reserved.

#include "DigimonWorldGameMode.h"
#include "Characters/TamerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADigimonWorldGameMode::ADigimonWorldGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/Tamers/BP_TamerCharacter"));
	if (DefaultPawnClass != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
