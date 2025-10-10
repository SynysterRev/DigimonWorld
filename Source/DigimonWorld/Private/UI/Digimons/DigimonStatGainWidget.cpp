// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonStatGainWidget.h"

#include "CommonTextBlock.h"
#include "Characters/PartnerDigimonCharacter.h"
#include "UI/Digimons/DigimonStatWidget.h"
#include "Data/DigimonGlobalData.h"

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

bool UDigimonStatGainWidget::UpdateStatFromGain(float DeltaTime)
{
	if (RemainingStatGain == 0 || BaseStat == nullptr)
		return false;

	const int32 MaxStat = BaseStat->StatType == EDigimonStatType::Health || BaseStat->StatType == EDigimonStatType::Mana
		                      ? MAX_HEALTH_MANA
		                      : MAX_OTHERS_STATS;
	RemainingStatGain = FMath::Clamp(RemainingStatGain - DeltaTime * StatGainSpeed, 0, MaxStat);
	CurrentBaseStat = FMath::Clamp(CurrentBaseStat + DeltaTime * StatGainSpeed, 0, MaxStat);
	BaseStat->SetStatValue(FMath::TruncToInt32(CurrentBaseStat));
	if (StatGain)
	{
		FString StatGainString = FString::Printf(TEXT("+%d"), FMath::TruncToInt32(RemainingStatGain));
		StatGain->SetText(FText::FromString(StatGainString));
	}
	return true;
}

void UDigimonStatGainWidget::SkipUpdateStat()
{
	if (RemainingStatGain == 0 || BaseStat == nullptr)
		return;

	CurrentBaseStat += RemainingStatGain;
	RemainingStatGain = 0;
	BaseStat->SetStatValue(CurrentBaseStat);
	if (StatGain)
	{
		FString StatGainString = FString::Printf(TEXT("+%d"), RemainingStatGain);
		StatGain->SetText(FText::FromString(StatGainString));
	}
}
