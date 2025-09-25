// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "DigimonUISubsystem.generated.h"

class UDigimonUISettings;
class UDigimonToiletSignWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogDigimonUISubsystem, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToiletAnimation);

UCLASS()
class DIGIMONWORLD_API UDigimonUISubsystem : public UCommonUISubsystemBase
{
	GENERATED_BODY()

private:
	bool bIsShowingToiletSign = false;
	
	UPROPERTY()
	TObjectPtr<UDigimonToiletSignWidget> ToiletSignWidget = nullptr;

	UFUNCTION()
	void ToiletSignAnimationEnd();

	UDigimonToiletSignWidget* GetOrCreateSignWidget();

	UPROPERTY(Transient)
	TObjectPtr<UDigimonUISettings> UISettings = nullptr;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void ShowToiletSign();

	FToiletAnimation OnToiletSignAnimationEnd;
};
