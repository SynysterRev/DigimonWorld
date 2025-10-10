// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonStatGainWidget.generated.h"

class UCommonTextBlock;
class UDigimonStatWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStatGainWidget : public UCommonUserWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatWidget> BaseStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> StatGain = nullptr;

	float CurrentBaseStat = 0;
	float RemainingStatGain = 0;

protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditInstanceOnly)
	float StatGainSpeed = 5.0f;

public:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	FText BaseStatText;

	void SetStatAndGain(int32 InBaseStat, int32 InStatGain);

	/**
	 * 
	 * @return True if still need to update, false otherwise
	 */
	bool UpdateStatFromGain(float DeltaTime);
	void SkipUpdateStat();
	
};
