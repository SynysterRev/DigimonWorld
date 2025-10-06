// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Data/DigimonUISettings.h"
#include "Settings/DigimonSettings.h"
#include "UI/ClockWidget.h"
#include "UI/StackWidget.h"
#include "UI/Digimons/DigimonToiletSignWidget.h"
#include "UI/Popup/StatsPopupWidget.h"

DEFINE_LOG_CATEGORY(LogDigimonUISubsystem);

void UDigimonUISubsystem::ToiletSignAnimationEnd()
{
	bIsShowingToiletSign = false;
	if (ToiletSignWidget)
	{
		ToiletSignWidget->OnShowAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
	}
	SetClockVisible(true);
	OnToiletSignAnimationEnd.Broadcast();
}

void UDigimonUISubsystem::StatsGainAnimationEnd()
{
	// if (UStackWidget* UIStack = GetOrCreateUIStack())
	// {
	// 	UIStack->PopLastWidget();
	// }
	SetClockVisible(true);
	OnStatsAnimationEnd.Broadcast();
}

UDigimonToiletSignWidget* UDigimonUISubsystem::GetOrCreateSignWidget()
{
	if (!UISettings)
		return nullptr;

	if (!ToiletSignWidget)
	{
		ToiletSignWidget = CreateWidget<UDigimonToiletSignWidget>(GetWorld(), UISettings->ToiletSignWidgetClass,
		                                                          TEXT("ToiletSignWidget"));
		if (ToiletSignWidget)
		{
			ToiletSignWidget->AddToViewport(10);
		}
	}
	return ToiletSignWidget;
}

UStatsPopupWidget* UDigimonUISubsystem::GetOrCreateStatsPopupWidget()
{
	if (!UISettings)
		return nullptr;

	UStatsPopupWidget* StatsPopupWidget = CreateWidget<UStatsPopupWidget>(GetWorld(), UISettings->StatsPopupWidgetClass,
	                                                                      TEXT("StatsPopupWidget"));
	if (UStackWidget* UIStack = GetOrCreateUIStack())
	{
		if (StatsPopupWidget)
		{
			UIStack->PushWidget(StatsPopupWidget);
		}
	}
	return StatsPopupWidget;
}

UStackWidget* UDigimonUISubsystem::GetOrCreateUIStack()
{
	if (!UISettings)
		return nullptr;

	if (!UIStackWidget)
	{
		UIStackWidget = CreateWidget<UStackWidget>(GetWorld(), UISettings->UIStackWidget, TEXT("UIStackWidget"));

		if (UIStackWidget)
		{
			UIStackWidget->AddToViewport(25);
		}
	}
	return UIStackWidget;
}

void UDigimonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (const UDigimonSettings* Settings = UDigimonSettings::GetDigimonWorldSettings())
	{
		if (Settings->DigimonUISettings.IsNull())
		{
			UE_LOG(LogDigimonUISubsystem, Error, TEXT("Digimon UI settings not referenced!"));
			return;
		}
		FSoftObjectPtr SoftObj(Settings->DigimonUISettings.ToSoftObjectPath());
		UISettings = Cast<UDigimonUISettings>(SoftObj.LoadSynchronous());
	}
}

void UDigimonUISubsystem::Deinitialize()
{
	bIsShowingToiletSign = false;
	if (ToiletSignWidget)
	{
		ToiletSignWidget->OnShowAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
		ToiletSignWidget->RemoveFromParent();
		ToiletSignWidget = nullptr;
	}
	if (UStackWidget* UIStack = GetOrCreateUIStack())
	{
		UIStack->PopAllWidget();
	}
	Super::Deinitialize();
}

void UDigimonUISubsystem::ShowToiletSign()
{
	if (bIsShowingToiletSign)
		return;

	if (UDigimonToiletSignWidget* ToiletSign = GetOrCreateSignWidget())
	{
		bIsShowingToiletSign = true;
		ToiletSign->PlayShowAnimation();
		SetClockVisible(false);
		ToiletSign->OnShowAnimationEnd.AddDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
	}
}

void UDigimonUISubsystem::ShowStatsPopup(const TMap<EDigimonStatType, int32>& TrainedStats)
{
	if (UStatsPopupWidget* PopupWidget = GetOrCreateStatsPopupWidget())
	{
		PopupWidget->InitializeStats(TrainedStats);
		PopupWidget->OpenPopup();
		SetClockVisible(false);
		PopupWidget->OnPopupClosed.AddDynamic(this, &UDigimonUISubsystem::StatsGainAnimationEnd);
	}
}

void UDigimonUISubsystem::SetClockVisible(bool bVisible) const
{
	if (ClockWidget)
		ClockWidget->SetClockVisible(bVisible);
}

void UDigimonUISubsystem::CreateClockWidget()
{
	if (!UISettings)
		return;

	if (!ClockWidget)
	{
		ClockWidget = CreateWidget<UClockWidget>(GetWorld(), UISettings->ClockWidgetClass, TEXT("ClockWidget"));

		if (ClockWidget)
		{
			ClockWidget->AddToViewport(20);
		}
	}
}
