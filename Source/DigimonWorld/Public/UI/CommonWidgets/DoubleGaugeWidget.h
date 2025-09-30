// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DoubleGaugeWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDoubleGaugeWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> LeftGauge;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> RightGauge;

	int32 MaxGaugeValue;
	int32 CurrentGaugeValue;

public:
	
	virtual void InitializeGauge(int32 InCurrentValue, int32 InMaxValue);
	
};
