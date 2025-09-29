// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DigimonBaseData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DigimonDataSubsystem.generated.h"

class APartnerDigimonCharacter;
class UDigimonGlobalsData;
DECLARE_LOG_CATEGORY_EXTERN(LogDigimonDataSubsystem, Log, All);

UCLASS()
class DIGIMONWORLD_API UDigimonDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	bool GetPartnerDigimonStats(const FName DigimonID, FDigimonPartnerData& OutPartnerData) const;
	bool GetEnemyDigimonStats(const FName DigimonID, FDigimonEnemyData& OutEnemyData) const;
	UDigimonGlobalsData* GetDigimonGlobalsData() const;

	APartnerDigimonCharacter* GetDigimonCharacter() const { return ActiveDigimon; }
	void SetDigimonCharacter(APartnerDigimonCharacter* InActiveDigimon) { ActiveDigimon = InActiveDigimon; }

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APartnerDigimonCharacter> ActiveDigimon;

	UPROPERTY()
	TObjectPtr<UDataTable> DigimonDataTable;

	UPROPERTY()
	TObjectPtr<UDigimonGlobalsData> DigimonGlobalsData;

	void OnDataTableLoaded();
	void LogAllPartnerRows() const;
};
