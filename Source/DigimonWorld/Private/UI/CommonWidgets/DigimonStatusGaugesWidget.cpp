// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CommonWidgets/DigimonStatusGaugesWidget.h"

#include "Components/DigimonLifeComponent.h"
#include "UI/CommonWidgets/DoubleGaugeWidget.h"
#include "UI/CommonWidgets/GaugeWidget.h"

void UDigimonStatusGaugesWidget::InitializeGauges(UDigimonLifeComponent* LifeComponent) const
{
	if (!LifeComponent)
		return;

	if (Happiness)
	{
		Happiness->InitializeGauge(LifeComponent->GetHappiness(), MAX_HAPPINESS);
	}

	if (Discipline)
	{
		Discipline->InitializeGauge(LifeComponent->GetDiscipline(), MAX_DISICPLINE);
	}

	if (Virus)
	{
		Virus->InitializeGauge(LifeComponent->GetVirusGauge(), MAX_VIRUS_BAR);
	}

	if (Tiredness)
	{
		Tiredness->InitializeGauge(LifeComponent->GetTiredness(), MAX_HAPPINESS);
	}
}
