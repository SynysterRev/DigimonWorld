// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/DigimonGlobalData.h"
#include "Engine/DataTable.h"
#include "SkillTableRow.generated.h"

class USkillEffect;
enum class EDigimonType : uint8;

UENUM(BlueprintType)
enum class ESkillRange : uint8
{
	D,
	C,
	B,
	A,
	S
};

USTRUCT(BlueprintType)
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDigimonType SkillType = EDigimonType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ManaCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillRange Range = ESkillRange::A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillEffect> SkillEffect;
};
