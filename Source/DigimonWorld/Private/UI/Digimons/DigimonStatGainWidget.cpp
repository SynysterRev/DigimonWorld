// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonStatGainWidget.h"

#include "CommonTextBlock.h"
#include "UI/Digimons/DigimonStatWidget.h"

void UDigimonStatGainWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (BaseStat && !BaseStatText.IsEmpty())
	{
		BaseStat->SetStatName(BaseStatText);
	}
}

void UDigimonStatGainWidget::SetStatAndGain(int32 InBaseStat, int32 InStatGain)
{
	if (BaseStat != nullptr)
	{
		BaseStat->SetStatValue(InBaseStat);
	}

	CurrentBaseStat = InBaseStat;

	if (StatGain)
	{
		StatGain->SetText(FText::AsNumber(InStatGain));
	}
	RemainingStatGain = InStatGain;
}

void UDigimonStatGainWidget::UpdateStatFromGain()
{
	if (RemainingStatGain == 0)
		return;
	
	if (BaseStat != nullptr)
	{
		RemainingStatGain--;
		CurrentBaseStat++;
		if (BaseStat != nullptr)
		{
			BaseStat->SetStatValue(CurrentBaseStat);
		}
		if (StatGain)
		{
			FString StatGainString = FString::Printf(TEXT("+%d"), RemainingStatGain);
			StatGain->SetText(FText::FromString(StatGainString));
		}
	}
}
