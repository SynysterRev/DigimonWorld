// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "CommonTextBlock.h"
#include "BaseInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UBaseInfoWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Title = nullptr;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Value = nullptr;

public:

	void SetTitle(const FText& NewTitle) const;
	void SetValue(const FText& NewValue) const;	
};
