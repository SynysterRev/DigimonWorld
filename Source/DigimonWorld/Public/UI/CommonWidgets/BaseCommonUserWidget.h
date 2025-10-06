// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "BaseCommonUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAnimation);

UCLASS()
class DIGIMONWORLD_API UBaseCommonUserWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> ShowAnimation;

	UFUNCTION()
	virtual void OnShowAnimFinished();

	void StopAndCleanupAnimation();

	FWidgetAnimationDynamicEvent AnimationFinishedDelegate;

	virtual void NativeDestruct() override;

public:

	virtual void PlayShowAnimation();
	
	FAnimation OnShowAnimationEnd;
	
};
