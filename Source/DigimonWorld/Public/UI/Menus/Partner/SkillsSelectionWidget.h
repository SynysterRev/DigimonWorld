// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SkillsSelectionWidget.generated.h"

class UUniformGridPanel;
class UGridPanel;
class UDigimonSkillButton;

USTRUCT(BlueprintType)
struct FSkillSelectionData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	int32 NumberSkillsPerType = 7;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	TObjectPtr<UDataTable> SkillsDataTable = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data")
	TSubclassOf<UDigimonSkillButton> SkillButtonClass;
};

UCLASS()
class DIGIMONWORLD_API USkillsSelectionWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category="Grid")
	TObjectPtr<UGridPanel> SkillGridPanel = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TArray<UDigimonSkillButton*> SkillButtons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Data")
	FSkillSelectionData SkillSelectionData;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
	virtual void NativePreConstruct() override;
	
};
