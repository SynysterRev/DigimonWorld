// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pause/PauseMenu.h"

#include "Subsystems/DigimonMenuSubsystem.h"
#include "UI/CommonWidgets/MenuButtonBase.h"

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

// bool UPauseMenu::NativeOnHandleBackAction()
// {
// 	if (UGameInstance* GameInstance = GetGameInstance())
// 	{
// 		if (UDigimonMenuSubsystem* MenuSubsystem = GameInstance->GetSubsystem<UDigimonMenuSubsystem>())
// 		{
// 			MenuSubsystem->ClosePauseMenu();
// 			return true;
// 		}
// 	}
// 	return false;
// }

void UPauseMenu::OpenPartnerInfo() const
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (UDigimonMenuSubsystem* MenuSubsystem = GameInstance->GetSubsystem<UDigimonMenuSubsystem>())
		{
			MenuSubsystem->OpenMenu("PartnerMenu");
		}
	}
}
