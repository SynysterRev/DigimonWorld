// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Partner/SkillsSelectionWidget.h"

#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"
#include "UI/Digimons/DigimonSkillButton.h"

void USkillsSelectionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!SkillSelectionData.SkillButtonClass)
	{
		return;
	}

	if (SkillGridPanel)
	{
		// SkillGridPanel->
		//
		// for (int32 col = 0; col < 10; ++col)
		// {
		// 	SkillGridPanel->SetColumnFill(col, 1.0f);
		// }
		for (int32 row = 0; row < SkillSelectionData.NumberSkillsPerType; ++row)
		{
			// SkillGridPanel->SetRowFill(row, 1.0f);
			for (int32 col = 0; col < 10; ++col)
			{
				auto* Button = CreateWidget<UDigimonSkillButton>(this, SkillSelectionData.SkillButtonClass);
				SkillGridPanel->AddChildToUniformGrid(Button, row, col);
			}
		}
	}
}
