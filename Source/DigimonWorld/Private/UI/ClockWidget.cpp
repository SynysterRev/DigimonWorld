// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ClockWidget.h"

#include "Components/TextBlock.h"
#include "Subsystems/DigimonTimeSubsystem.h"
#include "Utilities/DigimonSubsystems.h"

void UClockWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (auto* TimeSystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		TimeSystem->OnMinuteChanged.AddDynamic(this, &UClockWidget::OnMinuteChanged);

		OnMinuteChanged(TimeSystem->GetCurrentHourOfDay(),
		                TimeSystem->GetCurrentMinuteOfHour());
	}
}

void UClockWidget::NativeDestruct()
{
	if (auto* TimeSystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		TimeSystem->OnMinuteChanged.RemoveDynamic(this, &UClockWidget::OnMinuteChanged);
	}
	Super::NativeDestruct();
}

void UClockWidget::OnMinuteChanged(int32 NewHour, int32 NewMinute)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), NewHour, NewMinute)));
	}
}

void UClockWidget::SetClockVisible(bool bVisible)
{
	SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	if (auto* TimeSystem = UDigimonSubsystems::GetSubsystem<UDigimonTimeSubsystem>(this))
	{
		if (bVisible)
		{
			TimeSystem->ResumeTime();
		}
		else
		{
			TimeSystem->PauseTime();
		}
	}
}
