// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonUISettings.generated.h"

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

	UPROPERTY(EditAnywhere, Category= "UI")
	TSubclassOf<UStackWidget> UIStackWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UClockWidget> ClockWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UDigimonToiletSignWidget> ToiletSignWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="UI")
	TSubclassOf<UStatsPopupWidget> StatsPopupWidgetClass;
	
};
