// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/PauseMenu.h"

#include "Components/VerticalBox.h"
#include "Subsystems/DigimonUISubsystem.h"
#include "UI/StackWidget.h"
#include "UI/CommonWidgets/MenuButtonBase.h"
#include "Utilities/DigimonSubsystems.h"

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();
	PartnerButton->OnClicked().AddUObject(this, &UPauseMenu::OpenPartnerInfo);
	
	if (SubMenuStack)
	{
		SubMenuStack->OnDisplayedWidgetChanged().AddUObject(this, &UPauseMenu::OnSubMenuWidgetChanged);
	}
}

void UPauseMenu::NativeDestruct()
{
	PartnerButton->OnClicked().RemoveAll(this);
	Super::NativeDestruct();
}

UWidget* UPauseMenu::NativeGetDesiredFocusTarget() const
{
	if (SubMenuStack && SubMenuStack->GetActiveWidget())
	{
		return SubMenuStack->GetActiveWidget()->GetDesiredFocusTarget();
	}
	return PartnerButton;
}

TOptional<FUIInputConfig> UPauseMenu::GetDesiredInputConfig() const
{
	return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture, EMouseLockMode::DoNotLock);
}

bool UPauseMenu::NativeOnHandleBackAction()
{
	if (UDigimonUISubsystem* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		UISubsystem->ClosePauseMenu();
		return true;
	}

	return false;
}

void UPauseMenu::OnSubMenuWidgetChanged(UCommonActivatableWidget* NewWidget)
{
	SetMainMenuButtonsVisible(NewWidget == nullptr);
}

void UPauseMenu::OpenPartnerInfo()
{
	if (UDigimonUISubsystem* UISubsystem = UDigimonSubsystems::GetSubsystem<UDigimonUISubsystem>(this))
	{
		if (TSubclassOf<UCommonActivatableWidget>* PartnerClass = UISubsystem->GetMenuClass(FName("PartnerMenu")))
		{
			SubMenuStack->PushWidget(*PartnerClass);
			SetMainMenuButtonsVisible(false);
		}
	}
}

void UPauseMenu::SetMainMenuButtonsVisible(bool bVisible)
{
	if (ButtonsVerticalBox)
	{
		ButtonsVerticalBox->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
