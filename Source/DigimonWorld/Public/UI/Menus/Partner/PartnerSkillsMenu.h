// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PartnerSkillsMenu.generated.h"

class USkillsSelectionWidget;
class UVerticalBox;
class UDigimonSkillSlotWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UPartnerSkillsMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UDigimonSkillSlotWidget> FirstSkill = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> SpecialMove = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USkillsSelectionWidget> SkillsSelection = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> CurrentSkillsBox = nullptr;

	virtual void NativeConstruct() override;

	virtual bool NativeOnHandleBackAction() override;

	UFUNCTION()
	void OpenSkillsSelection();
};
