// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "DigimonUISubsystem.generated.h"

class UCommonActivatableWidget;
class UCommonActivatableWidgetContainerBase;
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

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	TSubclassOf<UCommonActivatableWidget>* GetMenuClass(FName MenuName) const;

	// --- MENUS ---
	void OpenPauseMenu();
	void ClosePauseMenu();
	void OpenMenu(const FName& MenuName);

	// --- POPUPS ---
	void ShowStatsPopup(const TMap<EDigimonStatType, int32>& TrainedStats);

	// --- HUD & GAMEPLAY ---
	void ShowToiletSign();
	void SetClockVisible(bool bVisible) const;

	UFUNCTION(BlueprintCallable, Category = "Digimon UI")
	void CreateClockWidget();

	UPROPERTY(BlueprintAssignable, Category = "Digimon UI | Events")
	FToiletAnimation OnToiletSignAnimationEnd;

	UPROPERTY(BlueprintAssignable, Category = "Digimon UI | Events")
	FStatsAnimation OnStatsAnimationEnd;

private:
	bool bIsShowingToiletSign = false;

	UPROPERTY(Transient)
	TObjectPtr<UDigimonUISettings> UISettings = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> UIRootWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UStackWidget> MenuStack = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UStackWidget> PopupStack = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UClockWidget> ClockWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UDigimonToiletSignWidget> ToiletSignWidget = nullptr;

	void EnsureUIRootCreated();

	UFUNCTION()
	void ToiletSignAnimationEnd();

	UFUNCTION()
	void StatsGainAnimationEnd();
};
