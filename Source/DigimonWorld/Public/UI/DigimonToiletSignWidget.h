// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonToiletSignWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToiletSignAnimation);

UCLASS()
class DIGIMONWORLD_API UDigimonToiletSignWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> DisplayAnimation;

	UFUNCTION()
	void OnToiletSignAnimFinished();

	void StopAndCleanupAnimation();

	FWidgetAnimationDynamicEvent AnimationFinishedDelegate;

public:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void PlayToiletAnimation();

	UPROPERTY()
	FToiletSignAnimation OnToiletSignAnimationEnd;
	
};
