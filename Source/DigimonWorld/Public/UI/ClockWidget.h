// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClockWidget.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UClockWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimeText;
    
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
    
	UFUNCTION()
	void OnMinuteChanged(int32 NewHour, int32 NewMinute);
};
