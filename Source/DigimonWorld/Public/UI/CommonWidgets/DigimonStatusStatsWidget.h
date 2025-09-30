// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonStatusStatsWidget.generated.h"

class UDigimonStatsComponent;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStatusStatsWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UCommonTextBlock> StrengthValue = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UCommonTextBlock> StaminaValue = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UCommonTextBlock> WisdomValue = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget), Category="Stats")
	TObjectPtr<UCommonTextBlock> SpeedValue = nullptr;

public:

	void InitializeStats(UDigimonStatsComponent* StatsComponent) const;
};
