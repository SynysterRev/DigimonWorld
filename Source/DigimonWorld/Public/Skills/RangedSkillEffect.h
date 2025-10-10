// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/SkillEffect.h"
#include "RangedSkillEffect.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API URangedSkillEffect : public USkillEffect
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Effect)
	TSubclassOf<AActor> ProjectileClass;

	void SpawnProjectile(AActor* Caster, AActor* Target);
	
};
