// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ClockWidget.h"

#include "Components/TextBlock.h"
#include "Subsystems/DigimonTimeSubsystem.h"

void UClockWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (auto* TimeSystem = GetGameInstance()->GetSubsystem<UDigimonTimeSubsystem>())
	{
		TimeSystem->OnMinuteChanged.AddDynamic(this, &UClockWidget::OnMinuteChanged);
        
		// Initialiser l'affichage
		OnMinuteChanged(FMath::FloorToInt(TimeSystem->GetCurrentTimeOfDay()), 
					   FMath::FloorToInt((TimeSystem->GetCurrentTimeOfDay() - 
					   FMath::FloorToInt(TimeSystem->GetCurrentTimeOfDay())) * 60.0f));
	}
}

void UClockWidget::OnMinuteChanged(int32 NewHour, int32 NewMinute)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), NewHour, NewMinute)));
	}
}
