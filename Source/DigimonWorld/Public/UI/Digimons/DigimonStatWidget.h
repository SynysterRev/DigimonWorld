// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonStatWidget.generated.h"

enum class EDigimonStatType : uint8;
class UCommonTextBlock;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStatWidget : public UCommonUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> StatName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> StatValue;

protected:

	virtual void NativePreConstruct() override;
	
public:

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	EDigimonStatType StatType;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FText StatText;

	void SetStatValue(int32 InStatValue) const;
	void SetStatName(const FText& InStatName) const;
};
