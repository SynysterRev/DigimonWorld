// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menus/Partner/PartnerMenu.h"

#include "CommonActivatableWidgetSwitcher.h"
#include "UI/CommonWidgets/MenuTabListWidgetBase.h"

void UPartnerMenu::NativeOnActivated()
{
	Super::NativeOnActivated();
	TabListWidget->SetLinkedSwitcher(MenuSwitcher);

	for (const FPartnerMenuData& MenuData : MenusData)
	{
		if (MenuData.MenuContentWidgetClass)
		{
			UCommonActivatableWidget* ContentWidget = CreateWidget<UCommonActivatableWidget>(
				this, MenuData.MenuContentWidgetClass);
			MenuSwitcher->AddChild(ContentWidget);
			TabListWidget->RegisterTab(MenuData.MenuNameID, MenuData.ButtonWidgetType, ContentWidget,
			                           MenuData.TabIndex);
		}
	}
}
