// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonUISettings.generated.h"

class UCommonActivatableWidget;
class UClockWidget;
class UDigimonToiletSignWidget;
class UStatsPopupWidget;
class UStackWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonUISettings : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "UI | Core")
	TSubclassOf<UUserWidget> UIRootClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI | HUD")
	TSubclassOf<UClockWidget> ClockWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI | HUD")
	TSubclassOf<UDigimonToiletSignWidget> ToiletSignWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI | Popups")
	TSubclassOf<UStatsPopupWidget> StatsPopupWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "UI | Menus")
	TMap<FName, TSubclassOf<UCommonActivatableWidget>> MenuWidgets;
	
};
