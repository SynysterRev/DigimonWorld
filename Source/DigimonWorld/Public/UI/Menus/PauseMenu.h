// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PauseMenu.generated.h"

class UVerticalBox;
class UStackWidget;
class UMenuButtonBase;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UPauseMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuButtonBase> PartnerButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> ButtonsVerticalBox = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStackWidget> SubMenuStack = nullptr;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

	virtual bool NativeOnHandleBackAction() override;
	void OnSubMenuWidgetChanged(UCommonActivatableWidget* NewWidget);

public:
	
	UFUNCTION()
	void OpenPartnerInfo();
	
	void SetMainMenuButtonsVisible(bool bVisible);
};
