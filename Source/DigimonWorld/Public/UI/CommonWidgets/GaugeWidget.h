// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GaugeWidget.generated.h"

class UProgressBar;
class UImage;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UGaugeWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> Gauge;

	int32 MaxGaugeValue;
	int32 CurrentGaugeValue;

public:
	
	virtual void InitializeGauge(int32 InCurrentValue, int32 InMaxValue);
};
