// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DigimonGlobalData.generated.h"

UENUM(BlueprintType)
enum class EDigimonActiveTime : uint8
{
	Baby UMETA(DisplayName = "Baby"),
	InTraining UMETA(DisplayName = "In-Training"),
	Day UMETA(DisplayName = "Day"),
	Groggy UMETA(DisplayName = "Groggy"),
	Night UMETA(DisplayName = "Night"),
	Sleepy UMETA(DisplayName = "Sleepy"),
	SunUp UMETA(DisplayName = "SunUp"),
	SunSet UMETA(DisplayName = "SunSet")
};

UENUM(BlueprintType)
enum class EDigimonBubbleType : uint8
{
	Hungry,
	Toilet,
	Battle,
	NoBattle
};

UENUM(BlueprintType)
enum class EDigimonAttribute : uint8
{
	Vaccine UMETA(DisplayName = "Vaccine"),
	Virus UMETA(DisplayName = "Virus"),
	Data UMETA(DisplayName = "Data"),
	Free UMETA(DisplayName = "Free")
};

UENUM(BlueprintType)
enum class EDigimonStatType : uint8
{
	Health,
	Mana,
	Attack,
	Defense,
	Speed,
	Brain
};

UENUM(BlueprintType)
enum class EDigimonStage : uint8
{
	Fresh UMETA(DisplayName = "Baby"),
	InTraining UMETA(DisplayName = "In-Training"),
	Rookie UMETA(DisplayName = "Rookie"),
	Champion UMETA(DisplayName = "Champion"),
	Ultimate UMETA(DisplayName = "Ultimate"),
	Mega UMETA(DisplayName = "Mega")
};

USTRUCT(BlueprintType)
struct FDigimonActivePeriod
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0, ClampMax= 23))
	int32 StartHour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0, ClampMax= 23))
	int32 EndHour;
};

UCLASS(BlueprintType)
class UDigimonGlobalsData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	TMap<EDigimonStage, int32> PoopHours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	TMap<EDigimonActiveTime, FDigimonActivePeriod> ActiveHours;

	// In game minutes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	int32 MaxTimeToFeedDigimon = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	float FavoriteFoodRefusalNotHungry = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	float FoodRefusalWhenHungry = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	float FoodRefusalNotHungry = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Digimon Rules")
	float ObjectRefusal = 0.2f;
};
