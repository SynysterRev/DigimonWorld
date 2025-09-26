// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonMenuSubsystem.h"

#include "CommonActivatableWidget.h"
#include "Data/DigimonMenuSettings.h"
#include "Settings/DigimonSettings.h"
#include "UI/MenuStack.h"

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

void UDigimonMenuSubsystem::OpenPauseMenu()
{
	if (!MenuSettings)
		return;
	if (UMenuStack* MenuStack = GetOrCreateMenuStack())
	{
		if (UCommonActivatableWidget* PauseMenu = GetOrCreateMenu("PauseMenu"))
		{
			MenuStack->PushWidget(PauseMenu);
		}
	}
}

void UDigimonMenuSubsystem::ClosePauseMenu()
{
	if (!MenuSettings)
		return;

	if (UMenuStack* MenuStack = GetOrCreateMenuStack())
	{
		if (UCommonActivatableWidget* PauseMenu = GetOrCreateMenu("PauseMenu"))
		{
			MenuStack->PopWidget(PauseMenu);
		}
	}
}

UCommonActivatableWidget* UDigimonMenuSubsystem::GetOrCreateMenu(FName MenuName)
{
	if (UCommonActivatableWidget* const* Found = MenuInstances.Find(MenuName))
	{
		return *Found;
	}

	if (TSubclassOf<UCommonActivatableWidget>* FoundClass = MenuSettings->MenuWidgets.Find(MenuName))
	{
		UCommonActivatableWidget* NewWidget = CreateWidget<UCommonActivatableWidget>(GetWorld(), *FoundClass);
		MenuInstances.Add(MenuName, NewWidget);
		return NewWidget;
	}

	return nullptr;
}

UMenuStack* UDigimonMenuSubsystem::GetOrCreateMenuStack()
{
	if (!MenuSettings)
		return nullptr;

	if (!MenuStackWidget)
	{
		MenuStackWidget = CreateWidget<UMenuStack>(GetWorld(), MenuSettings->MenuStackWidget, TEXT("MenuStackWidget"));

		if (MenuStackWidget)
		{
			MenuStackWidget->AddToViewport(15);
		}
	}
	return MenuStackWidget;
}
