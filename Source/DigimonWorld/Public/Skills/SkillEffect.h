// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillEffect.generated.h"


struct FSkillData;

UCLASS(Blueprintable, Abstract)
class DIGIMONWORLD_API USkillEffect : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	virtual void ExecuteSkill(AActor* Caster, AActor* Target, const FSkillData& SkillData);
	
};
