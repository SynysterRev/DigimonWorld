// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/DoubleGaugeWidget.h"

#include "Components/ProgressBar.h"

void UDoubleGaugeWidget::InitializeGauge(int32 InCurrentValue, int32 InMaxValue)
{
	CurrentGaugeValue = InCurrentValue;
	MaxGaugeValue = InMaxValue;

	float HalfMax = MaxGaugeValue / 2.0f;
	float NormalizedValue = CurrentGaugeValue / HalfMax;

	if (LeftGauge)
	{
		LeftGauge->SetPercent(FMath::Clamp(1.0f - NormalizedValue, 0.0f, 1.0f));
	}
    
	if (RightGauge)
	{
		RightGauge->SetPercent(FMath::Clamp(NormalizedValue - 1.0f, 0.0f, 1.0f));
	}
}
