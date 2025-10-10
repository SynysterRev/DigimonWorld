// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BasePopupWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPopupAnimation);

UCLASS()
class DIGIMONWORLD_API UBasePopupWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	UBasePopupWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Popup")
	virtual void OpenPopup();

	UPROPERTY(BlueprintAssignable, Category = "Popup")
	FPopupAnimation OnPopupClosed;

	UPROPERTY(BlueprintAssignable, Category = "Popup")
	FPopupAnimation OnPopupOpened;

protected:
	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UFUNCTION(BlueprintCallable, Category = "Popup")
	virtual void OnConfirmAction();
    
	UFUNCTION(BlueprintCallable, Category = "Popup")
	virtual void OnCancelAction();

	UFUNCTION(BlueprintCallable, Category = "Popup")
	void ClosePopup();

	UFUNCTION(BlueprintCallable, Category = "Popup")
	void SetInputEnabled(bool bEnabled);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (ExposeOnSpawn = true, RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle TriggeringInputAction;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> OpenAnimation;

	UFUNCTION()
	virtual void PopupOpened();

	void StopAndCleanupAnimation();

	FWidgetAnimationDynamicEvent AnimationFinishedDelegate;
	
	bool bInputEnabled = true;
private:
	
	FUIActionBindingHandle ConfirmHandle;
	FUIActionBindingHandle CancelHandle;
	
};
