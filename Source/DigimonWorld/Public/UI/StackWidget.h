// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "StackWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UStackWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> Stack = nullptr;

public:
	template <typename T = UCommonActivatableWidget>
	T* PushWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass, TFunctionRef<void(T&)> InitFunc) const
	{
		if (!Stack || !WidgetClass)
			return nullptr;
		return Stack->AddWidget<T>(WidgetClass, InitFunc);
	}
	UCommonActivatableWidget* PushWidget(TSubclassOf<UCommonActivatableWidget> WidgetClass) const
	{
		if (!Stack || !WidgetClass) return nullptr;
		return Stack->AddWidget<UCommonActivatableWidget>(WidgetClass);
	}
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnStackWidgetChanged, UCommonActivatableWidget*);
    
	auto& OnDisplayedWidgetChanged() const 
	{ 
		return Stack->OnDisplayedWidgetChanged(); 
	}
	void PopWidget(UCommonActivatableWidget* ActivatableWidget) const;
	void PopLastWidget() const;
	void PopAllWidget() const;
	UCommonActivatableWidget* GetActiveWidget() const;
	int32 GetTotalActiveWidgets() const;
};
