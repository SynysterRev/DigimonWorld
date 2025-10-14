// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "Skills/SkillTableRow.h"
#include "DigimonSkillButton.generated.h"

class UImage;

UCLASS()
class DIGIMONWORLD_API UDigimonSkillButton : public UCommonButtonBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UImage> SkillIcon = nullptr;

	UPROPERTY(BlueprintReadOnly)
	FSkillData SkillData;

public:
	void SetSkillData(const FSkillData& InSkillData);
};
