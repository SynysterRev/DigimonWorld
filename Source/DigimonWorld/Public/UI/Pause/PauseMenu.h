// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PauseMenu.generated.h"

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

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual UWidget* NativeGetDesiredFocusTarget() const override;

	// virtual bool NativeOnHandleBackAction() override;
	

public:
	
	UFUNCTION()
	void OpenPartnerInfo() const;
	
};
