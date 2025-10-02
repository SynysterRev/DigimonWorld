// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonBubbleIndicatorWidget.h"

DEFINE_LOG_CATEGORY(LogDigimonBubbleWidget);

void UDigimonBubbleIndicatorWidget::AddBubbleType(EDigimonBubbleType BubbleType)
{
	if (!ActiveBubbles.Contains(BubbleType))
	{
		ActiveBubbles.Add(BubbleType);
		if (ActiveBubbles.Num() == 1)
		{
			OnNeedChanged(BubbleType);
			UpdateRotationTimer();
			SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UDigimonBubbleIndicatorWidget::RemoveBubbleType(EDigimonBubbleType BubbleType)
{
	if (ActiveBubbles.Contains(BubbleType))
	{
		ActiveBubbles.Remove(BubbleType);
	}
	// if (ActiveBubbles.Num() == 0)
	// {
	// 	SetVisibility(ESlateVisibility::Hidden);
	// 	if (UWorld* World = GetWorld())
	// 	{
	// 		World->GetTimerManager().ClearTimer(RotationTimer);
	// 	}
	// }
	// else
	// {
	// 	CurrentNeedIndex = FMath::Min(CurrentNeedIndex, ActiveBubbles.Num() - 1);
	// }
}

void UDigimonBubbleIndicatorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateRotationTimer();
}

void UDigimonBubbleIndicatorWidget::NativeDestruct()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(RotationTimer);
	}
	Super::NativeDestruct();
}

void UDigimonBubbleIndicatorWidget::RotateToNextNeed()
{
	if (!IsValid(this) || !GetWorld())
	{
		return;
	}

	if (ActiveBubbles.Num() > 0)
	{
		CurrentNeedIndex = (CurrentNeedIndex + 1) % ActiveBubbles.Num();
		OnNeedChanged(ActiveBubbles[CurrentNeedIndex]);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().ClearTimer(RotationTimer);
		}
	}
}

void UDigimonBubbleIndicatorWidget::UpdateRotationTimer()
{
	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(RotationTimer);
	if (ActiveBubbles.Num() > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(
			RotationTimer,
			this,
			&UDigimonBubbleIndicatorWidget::RotateToNextNeed,
			RotationInterval,
			true
		);
	}
}
