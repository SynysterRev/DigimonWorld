// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PartnerStatusWidget.generated.h"

class UDigimonStatusGaugesWidget;
class UDigimonStatusStatsWidget;
class APartnerDigimonCharacter;
class UBaseInfoWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UPartnerStatusWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Type = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Stage = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Age = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Weight = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Nature = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> Attribute = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> ActivePeriod = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> HealthPoints = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBaseInfoWidget> ManaPoints = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatusStatsWidget> StatsWidget = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDigimonStatusGaugesWidget> GaugesWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<APartnerDigimonCharacter> CurrentDigimon = nullptr;

	void InitializeStats() const;
	void InitializeInfo() const;

public:

	virtual void NativeConstruct() override;
	
};
