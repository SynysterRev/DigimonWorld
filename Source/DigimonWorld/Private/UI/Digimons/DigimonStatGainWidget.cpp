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
		if (InStatGain > 0)
		{
			FString StatGainString = FString::Printf(TEXT("+%d"), InStatGain);
			StatGain->SetText(FText::FromString(StatGainString));
		}
		else
		{
			StatGain->SetText(FText::FromString(""));
		}
	}
	RemainingStatGain = InStatGain;
}

bool UDigimonStatGainWidget::UpdateStatFromGain()
{
	if (RemainingStatGain == 0 || BaseStat == nullptr)
		return false;
	
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
	return true;
}
