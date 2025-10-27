// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Partner/SkillsSelectionWidget.h"

#include "Components/GridPanel.h"
#include "Components/UniformGridPanel.h"
#include "UI/Digimons/DigimonSkillButton.h"

UWidget* USkillsSelectionWidget::NativeGetDesiredFocusTarget() const
{
	return SkillButtons.Num() > 0 ? SkillButtons[0] : nullptr;
}

void USkillsSelectionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!SkillSelectionData.SkillButtonClass)
	{
		return;
	}

	if (SkillGridPanel)
	{
		TArray<FSkillData*> Rows;
		SkillSelectionData.SkillsDataTable->GetAllRows(TEXT("SkillData"), Rows);
		int32 SkillCount = 0;
		for (int32 col = 1; col < 10; ++col)
		{
			for (int32 row = 0; row < SkillSelectionData.NumberSkillsPerType; ++row)
			{
				auto* Button = CreateWidget<UDigimonSkillButton>(this, SkillSelectionData.SkillButtonClass);
				if (Button)
				{
					if (SkillCount < Rows.Num())
					{
						Button->SetSkillData(*Rows[SkillCount]);
					}
					SkillButtons.Add(Button);
					SkillGridPanel->AddChildToGrid(Button, row + 1, col);
				}
				SkillCount++;
			}
		}
	}
}
