// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DigimonBubbleIndicatorWidget.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDigimonBubbleWidget, Log, All);


enum class EDigimonBubbleType : uint8;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonBubbleIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void AddBubbleType(EDigimonBubbleType BubbleType);
	void RemoveBubbleType(EDigimonBubbleType BubbleType);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(Transient)
	TArray<EDigimonBubbleType> ActiveBubbles;

	UPROPERTY(BlueprintReadOnly, Category = "Needs")
	int32 CurrentNeedIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float RotationInterval = 2.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void OnNeedChanged(EDigimonBubbleType NewBubble);

	FTimerHandle RotationTimer;

private:
	void RotateToNextNeed();
	void UpdateRotationTimer();
};
