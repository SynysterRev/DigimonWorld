// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonMenuSettings.generated.h"

class UStackWidget;
class UCommonActivatableWidget;

UCLASS()
class DIGIMONWORLD_API UDigimonMenuSettings : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category= "Menu")
	TSubclassOf<UStackWidget> MenuStackWidget;
	
	UPROPERTY(EditAnywhere, Category= "Menu")
	TMap<FName, TSubclassOf<UCommonActivatableWidget>> MenuWidgets;
};
