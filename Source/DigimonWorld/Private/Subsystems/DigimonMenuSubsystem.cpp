// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonMenuSubsystem.h"

#include "CommonActivatableWidget.h"
#include "Data/DigimonMenuSettings.h"
#include "Settings/DigimonSettings.h"
#include "Subsystems/DigimonUISubsystem.h"
#include "UI/StackWidget.h"
#include "Utilities/DigimonSubsystems.h"

DEFINE_LOG_CATEGORY(LogDigimonMenuSubsystem);

void UDigimonMenuSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (const UDigimonSettings* Settings = UDigimonSettings::GetDigimonWorldSettings())
	{
		if (Settings->DigimonMenuSettings.IsNull())
		{
			UE_LOG(LogDigimonMenuSubsystem, Error, TEXT("Digimon Menu settings not referenced!"));
			return;
		}
		FSoftObjectPtr SoftObj(Settings->DigimonMenuSettings.ToSoftObjectPath());
		MenuSettings = Cast<UDigimonMenuSettings>(SoftObj.LoadSynchronous());
	}
}

void UDigimonMenuSubsystem::Deinitialize()
{
	if (MenuStackWidget)
	{
		MenuStackWidget->PopAllWidget();
	}
	Super::Deinitialize();
}

void UDigimonMenuSubsystem::OpenPauseMenu()
{
	OpenMenu(FName("PauseMenu"));
}

void UDigimonMenuSubsystem::ClosePauseMenu()
{
	if (MenuStackWidget)
	{
		MenuStackWidget->PopLastWidget();
		// MenuStackWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (auto* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		UISubsystem->SetClockVisible(true);
	}
}

void UDigimonMenuSubsystem::OpenMenu(const FName& MenuName)
{
	if (!MenuSettings)
       return;

    UStackWidget* MenuStack = GetOrCreateMenuStack();
    if (!MenuStack)
       return;

    if (TSubclassOf<UCommonActivatableWidget>* FoundClass = MenuSettings->MenuWidgets.Find(MenuName))
    {
        MenuStack->SetVisibility(ESlateVisibility::Visible);
        
        MenuStack->PushWidget(*FoundClass);

        if (auto* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
        {
           UISubsystem->SetClockVisible(false);
        }
    }
}

UStackWidget* UDigimonMenuSubsystem::GetOrCreateMenuStack()
{
	if (!MenuSettings)
		return nullptr;

	if (!MenuStackWidget)
	{
		MenuStackWidget = CreateWidget<UStackWidget>(GetWorld(), MenuSettings->MenuStackWidget, TEXT("MenuStackWidget"));

		if (MenuStackWidget)
		{
			MenuStackWidget->AddToViewport(15);
		}
	}
	return MenuStackWidget;
}
