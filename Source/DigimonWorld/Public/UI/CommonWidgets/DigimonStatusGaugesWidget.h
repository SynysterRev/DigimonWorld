// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "DigimonStatusGaugesWidget.generated.h"

class UDigimonLifeComponent;
class UGaugeWidget;
class UDoubleGaugeWidget;
/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStatusGaugesWidget : public UCommonUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDoubleGaugeWidget> Happiness;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UDoubleGaugeWidget> Discipline;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGaugeWidget> Virus;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UGaugeWidget> Tiredness;

public:

	void InitializeGauges(UDigimonLifeComponent* LifeComponent) const;
	
};
