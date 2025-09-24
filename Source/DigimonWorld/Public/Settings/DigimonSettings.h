// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "DigimonSettings.generated.h"


class UDigimonGlobalsData;

UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="Digimon World Settings"))
class DIGIMONWORLD_API UDigimonSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Data Tables", 
			  meta = (DisplayName = "Digimon Data Table"))
	TSoftObjectPtr<UDataTable> DigimonDataTable;

	UPROPERTY(EditAnywhere, Config)
	TSoftObjectPtr<UDigimonGlobalsData> DigimonGlobalsData;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	static const UDigimonSettings* GetDigimonWorldSettings();
	
};
