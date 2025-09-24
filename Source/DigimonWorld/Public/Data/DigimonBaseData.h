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
	int32 BaseHealth;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseMana;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseAttack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseDefense;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int32 BaseBrain;
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
	EDigimonAttribute DigimonAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	EDigimonStage DigimonStage;

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
	EDigimonActiveTime DigimonActiveTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EDigimonStatType, int32> TrainingModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> HungryHours; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 HungerThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FatigueRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PoopSize;
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
