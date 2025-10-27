// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Partner/PartnerSkillsMenu.h"

#include "Components/VerticalBox.h"
#include "UI/Digimons/DigimonSkillSlotWidget.h"
#include "UI/Menus/Partner/SkillsSelectionWidget.h"

void UPartnerSkillsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (FirstSkill)
	{
		FirstSkill->OnClicked().AddUObject(this, &UPartnerSkillsMenu::OpenSkillsSelection);
	}
}

bool UPartnerSkillsMenu::NativeOnHandleBackAction()
{
	UE_LOG(LogTemp, Error, TEXT("Activateikjsnd"));
	return Super::NativeOnHandleBackAction();
}

void UPartnerSkillsMenu::OpenSkillsSelection()
{
	if (SpecialMove)
	{
		SpecialMove->SetVisibility(ESlateVisibility::Collapsed);
	}
	if (CurrentSkillsBox)
	{
		CurrentSkillsBox->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	if (SkillsSelection)
	{
		SkillsSelection->SetVisibility(ESlateVisibility::Visible);
		SkillsSelection->ActivateWidget();
	}
}
