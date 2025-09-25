// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DigimonGlobalData.h"
#include "DigimonBaseData.generated.h"

USTRUCT(BlueprintType)
struct DIGIMONWORLD_API FDigimonStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseHealth = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseMana = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseAttack = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseDefense = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseSpeed = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseBrain= 50;
};

USTRUCT(BlueprintType)
struct DIGIMONWORLD_API FDigimonBaseData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DigimonID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	EDigimonAttribute DigimonAttribute = EDigimonAttribute::Vaccine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	EDigimonStage DigimonStage = EDigimonStage::Rookie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDigimonStats DigimonStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Portrait;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> SkeletalMesh;
};

USTRUCT(BlueprintType)
struct DIGIMONWORLD_API FDigimonPartnerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDigimonBaseData DigimonBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDigimonActiveTime DigimonActiveTime = EDigimonActiveTime::Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDigimonStatType, int32> TrainingModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> HungryHours; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HungerThreshold = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FatigueRate = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAge = 4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxEnergy = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Weight = 15;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PoopSize = 8;
};

USTRUCT(BlueprintType)
struct DIGIMONWORLD_API FDigimonEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDigimonBaseData DigimonBaseData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> LootTable;
};
