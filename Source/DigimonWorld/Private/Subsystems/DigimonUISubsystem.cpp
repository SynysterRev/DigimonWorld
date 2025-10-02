// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonUISubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Data/DigimonUISettings.h"
#include "Settings/DigimonSettings.h"
#include "UI/Digimons/DigimonToiletSignWidget.h"

DEFINE_LOG_CATEGORY(LogDigimonUISubsystem);

void UDigimonUISubsystem::ToiletSignAnimationEnd()
{
	bIsShowingToiletSign = false;
	if (ToiletSignWidget)
	{
		ToiletSignWidget->OnToiletSignAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
	}
	OnToiletSignAnimationEnd.Broadcast();
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
		ToiletSignWidget->OnToiletSignAnimationEnd.RemoveDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
		ToiletSignWidget->RemoveFromParent();
		ToiletSignWidget = nullptr;
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
		ToiletSign->PlayToiletAnimation();
		ToiletSign->OnToiletSignAnimationEnd.AddDynamic(this, &UDigimonUISubsystem::ToiletSignAnimationEnd);
	}
}
