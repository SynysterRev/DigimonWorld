// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDigimonType SkillType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Power;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ManaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESkillRange Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<USkillEffect> SkillEffect;
};
