// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Pause/PauseMenu.h"

#include "UI/CommonWidgets/MenuButtonBase.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	PartnerButton->OnClicked().AddUObject(this, &UPauseMenu::Test);
}

UWidget* UPauseMenu::NativeGetDesiredFocusTarget() const
{
	return PartnerButton;
}

void UPauseMenu::Test()
{
	UE_LOG(LogTemp, Log, TEXT("Bouton cliqué !"));
}
