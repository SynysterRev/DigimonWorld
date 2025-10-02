// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonStatusStatsWidget.generated.h"

class UDigimonStatsComponent;
class UDigimonStatWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStatusStatsWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UDigimonStatWidget> StrengthStat = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UDigimonStatWidget> StaminaStat = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UDigimonStatWidget> WisdomStat = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UDigimonStatWidget> SpeedStat = nullptr;

public:

	void InitializeStats(UDigimonStatsComponent* StatsComponent) const;
};
