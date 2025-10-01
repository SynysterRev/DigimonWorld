// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/PauseMenu.h"

#include "Subsystems/DigimonMenuSubsystem.h"
#include "UI/CommonWidgets/MenuButtonBase.h"
#include "Utilities/DigimonSubsystems.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	PartnerButton->OnClicked().AddUObject(this, &UPauseMenu::OpenPartnerInfo);
}

void UPauseMenu::NativeDestruct()
{
	PartnerButton->OnClicked().RemoveAll(this);
	Super::NativeDestruct();
}

UWidget* UPauseMenu::NativeGetDesiredFocusTarget() const
{
	return PartnerButton;
}

bool UPauseMenu::NativeOnHandleBackAction()
{
	if (UDigimonMenuSubsystem* MenuSubsystem = UDigimonSubsystems::GetSubsystem<UDigimonMenuSubsystem>(this))
	{
		MenuSubsystem->ClosePauseMenu();
		return true;
	}
	return false;
}

void UPauseMenu::OpenPartnerInfo() const
{
	if (UDigimonMenuSubsystem* MenuSubsystem = UDigimonSubsystems::GetSubsystem<UDigimonMenuSubsystem>(this))
	{
		MenuSubsystem->OpenMenu("PartnerMenu");
	}
}
