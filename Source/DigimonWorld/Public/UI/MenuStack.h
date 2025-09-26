// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "MenuStack.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UMenuStack : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack = nullptr;

public:

	void PushWidget(UCommonActivatableWidget* ActivatableWidget) const;
	void PopWidget(UCommonActivatableWidget* ActivatableWidget) const;
	void PopLastWidget() const;
	
};
