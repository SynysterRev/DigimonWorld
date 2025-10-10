// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RangedSkillEffect.h"
#include "HeatBreathEffect.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UHeatBreathEffect : public URangedSkillEffect
{
	GENERATED_BODY()

protected:

	virtual void SpawnProjectile(AActor* Caster, AActor* Target) override;
	
};
