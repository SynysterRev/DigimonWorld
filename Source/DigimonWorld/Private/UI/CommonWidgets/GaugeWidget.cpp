// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/GaugeWidget.h"

#include "Components/ProgressBar.h"

void UGaugeWidget::InitializeGauge(int32 InCurrentValue, int32 InMaxValue)
{
	CurrentGaugeValue = InCurrentValue;
	MaxGaugeValue = InMaxValue;

	if (Gauge)
	{
		Gauge->SetPercent(CurrentGaugeValue / static_cast<float>(MaxGaugeValue));
	}
}
