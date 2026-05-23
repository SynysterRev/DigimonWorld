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

void UDigimonUISubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const UDigimonSettings* Settings = UDigimonSettings::GetDigimonWorldSettings())
	{
		if (!Settings->DigimonUISettings.IsNull())
		{
			FSoftObjectPtr SoftObj(Settings->DigimonUISettings.ToSoftObjectPath());
			UISettings = Cast<UDigimonUISettings>(SoftObj.LoadSynchronous());
		}
		else
		{
			UE_LOG(LogDigimonUISubsystem, Error, TEXT("Digimon UI settings not referenced in DigimonSettings!"));
		}
	}
}

void UDigimonUISubsystem::Deinitialize()
{
	bIsShowingToiletSign = false;

	if (ToiletSignWidget)
	{
		ToiletSignWidget->OnShowAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
		ToiletSignWidget = nullptr;
	}

	if (UIRootWidget)
	{
		UIRootWidget->RemoveFromParent();
		UIRootWidget = nullptr;
	}

	Super::Deinitialize();
}

TSubclassOf<UCommonActivatableWidget>* UDigimonUISubsystem::GetMenuClass(FName MenuName) const
{
	if (!UISettings || UISettings->MenuWidgets.IsEmpty())
	{
		return nullptr;
	}
	
	return UISettings->MenuWidgets.Find(MenuName);
}

void UDigimonUISubsystem::EnsureUIRootCreated()
{
	if (UIRootWidget || !UISettings || !UISettings->UIRootClass)
		return;

	UIRootWidget = CreateWidget<UUserWidget>(GetWorld(), UISettings->UIRootClass, TEXT("UIRoot"));
	if (UIRootWidget)
	{
		UIRootWidget->AddToViewport(10);

		MenuStack = Cast<UStackWidget>(UIRootWidget->GetWidgetFromName(TEXT("MenuStack")));
		PopupStack = Cast<UStackWidget>(UIRootWidget->GetWidgetFromName(TEXT("PopupStack")));

		ClockWidget = Cast<UClockWidget>(UIRootWidget->GetWidgetFromName(TEXT("ClockWidget")));
		ToiletSignWidget = Cast<UDigimonToiletSignWidget>(UIRootWidget->GetWidgetFromName(TEXT("ToiletSignWidget")));
	}

	if (!MenuStack || !PopupStack)
	{
		UE_LOG(LogDigimonUISubsystem, Warning,
		       TEXT("EnsureUIRootCreated: One or more Stacks are missing from WBP_UIRoot!"));
	}
}

// ==========================================
// --- MENUS ---
// ==========================================

void UDigimonUISubsystem::OpenPauseMenu()
{
	OpenMenu(FName("PauseMenu"));
}

void UDigimonUISubsystem::ClosePauseMenu()
{
	if (MenuStack)
	{
		MenuStack->PopLastWidget();
	}
	SetClockVisible(true);
}

void UDigimonUISubsystem::OpenMenu(const FName& MenuName)
{
	EnsureUIRootCreated();
	if (!MenuStack || !UISettings) return;

	if (TSubclassOf<UCommonActivatableWidget>* FoundClass = UISettings->MenuWidgets.Find(MenuName))
	{
		MenuStack->PushWidget(*FoundClass);
		SetClockVisible(false);
	}
}

// ==========================================
// --- POPUPS ---
// ==========================================

void UDigimonUISubsystem::ShowStatsPopup(const TMap<EDigimonStatType, int32>& TrainedStats)
{
	EnsureUIRootCreated();
	if (!PopupStack || !UISettings || !UISettings->StatsPopupWidgetClass) return;

	PopupStack->PushWidget<UStatsPopupWidget>(UISettings->StatsPopupWidgetClass,
	                                          [this, &TrainedStats](UStatsPopupWidget& PopupWidget)
	                                          {
		                                          PopupWidget.InitializeStats(TrainedStats);
		                                          PopupWidget.OnPopupClosed.AddDynamic(
			                                          this, &UDigimonUISubsystem::StatsGainAnimationEnd);
		                                          PopupWidget.OpenPopup();
	                                          });

	SetClockVisible(false);
}

void UDigimonUISubsystem::StatsGainAnimationEnd()
{
	SetClockVisible(true);
	OnStatsAnimationEnd.Broadcast();
}

// ==========================================
// --- HUD & GAMEPLAY ---
// ==========================================

void UDigimonUISubsystem::ShowToiletSign()
{
	if (bIsShowingToiletSign || !ToiletSignWidget) return;

	bIsShowingToiletSign = true;
	ToiletSignWidget->SetVisibility(ESlateVisibility::Visible);
	ToiletSignWidget->PlayShowAnimation();
	SetClockVisible(false);
	ToiletSignWidget->OnShowAnimationEnd.AddDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
}

void UDigimonUISubsystem::ToiletSignAnimationEnd()
{
	bIsShowingToiletSign = false;
    
	if (ToiletSignWidget)
	{
		ToiletSignWidget->OnShowAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
		ToiletSignWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
    
	SetClockVisible(true);
	OnToiletSignAnimationEnd.Broadcast();
}

void UDigimonUISubsystem::CreateClockWidget()
{
	EnsureUIRootCreated();
	if (ClockWidget)
	{
		ClockWidget->SetClockVisible(true);
	}
}

void UDigimonUISubsystem::SetClockVisible(bool bVisible) const
{
	if (ClockWidget)
	{
		ClockWidget->SetClockVisible(bVisible);
	}
}
