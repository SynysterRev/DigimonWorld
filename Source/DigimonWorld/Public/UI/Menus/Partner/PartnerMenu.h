// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PartnerMenu.generated.h"

class UCommonButtonBase;
class UMenuTabListWidgetBase;
class UCommonActivatableWidgetSwitcher;

USTRUCT(BlueprintType)
struct FPartnerMenuData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int32 TabIndex = 0;

	UPROPERTY(EditAnywhere)
	FName MenuNameID = "";

	UPROPERTY(EditAnywhere)
	// TObjectPtr<UWidget> MenuContent;
	TSubclassOf<UCommonActivatableWidget> MenuContentWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCommonButtonBase> ButtonWidgetType;

	UPROPERTY(EditAnywhere)
	FText MenuDisplayText;
};

UCLASS()
class DIGIMONWORLD_API UPartnerMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()

	int32 TabIndex = 0;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetSwitcher> MenuSwitcher = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UMenuTabListWidgetBase> TabListWidget = nullptr;

	virtual void NativeOnActivated() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Menu)
	TArray<FPartnerMenuData> MenusData;
};
