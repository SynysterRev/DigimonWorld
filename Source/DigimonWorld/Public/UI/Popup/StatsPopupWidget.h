// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePopupWidget.h"
#include "StatsPopupWidget.generated.h"

enum class EDigimonStatType : uint8;
class UDigimonStatsComponent;
class UDigimonStatGainWidget;

UCLASS()
class DIGIMONWORLD_API UStatsPopupWidget : public UBasePopupWidget
{
	GENERATED_BODY()

private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> HealthStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> ManaStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> StrengthStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> StaminaStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> WisdomStat = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatGainWidget> SpeedStat = nullptr;

	UDigimonStatsComponent* GetDigimonStatsComp() const;

	TMap<EDigimonStatType, TObjectPtr<UDigimonStatGainWidget>> StatWidgets;

protected:

	virtual void NativeConstruct() override;
	virtual void PopupOpened() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void OnConfirmAction() override;
	void UpdateStats();

	bool bUpdateStatsFromGain = false;

public:

	void InitializeStats(const TMap<EDigimonStatType, int32>& TrainedStats);
};
