// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Digimons/DigimonSkillButton.h"
#include "Styling/SlateBrush.h"
#include "Components/Image.h"

void UDigimonSkillButton::SetSkillData(const FSkillData& InSkillData)
{
	SkillData = InSkillData;

	if (SkillIcon)
	{
		FSlateBrush SkillBrush;
		SkillBrush.SetResourceObject(SkillData.Icon);
		SkillIcon->SetBrush(SkillBrush);
	}
}
