// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "DigimonUISubsystem.generated.h"

class UClockWidget;
enum class EDigimonStatType : uint8;
class UStatsPopupWidget;
class UDigimonUISettings;
class UDigimonToiletSignWidget;
class UStackWidget;

DECLARE_LOG_CATEGORY_EXTERN(LogDigimonUISubsystem, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToiletAnimation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatsAnimation);

UCLASS()
class DIGIMONWORLD_API UDigimonUISubsystem : public UCommonUISubsystemBase
{
	GENERATED_BODY()

private:
	bool bIsShowingToiletSign = false;

	UPROPERTY(Transient)
	TObjectPtr<UStackWidget> UIStackWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UDigimonToiletSignWidget> ToiletSignWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UStatsPopupWidget> StatsPopupWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UClockWidget> ClockWidget = nullptr;

	UFUNCTION()
	void ToiletSignAnimationEnd();

	UFUNCTION()
	void StatsGainAnimationEnd();

	UDigimonToiletSignWidget* GetOrCreateSignWidget();
	UStatsPopupWidget* GetOrCreateStatsPopupWidget();

	UPROPERTY(Transient)
	TObjectPtr<UDigimonUISettings> UISettings = nullptr;

	UStackWidget* GetOrCreateUIStack();	

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	void ShowToiletSign();
	void ShowStatsPopup(const TMap<EDigimonStatType, int32>& TrainedStats);
	void SetClockVisible(bool bVisible) const;

	UFUNCTION(BlueprintCallable)
	void CreateClockWidget();

	FToiletAnimation OnToiletSignAnimationEnd;

	FStatsAnimation OnStatsAnimationEnd;
};
