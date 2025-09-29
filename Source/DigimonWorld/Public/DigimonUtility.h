// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

enum class EDigimonAttribute : uint8;
enum class EDigimonStage : uint8;
/**
 * 
 */

struct DIGIMONWORLD_API FDigimonUtility
{
	static FText GetTextForDigimonStage(EDigimonStage DigimonStage);
	static FText GetTextForDigimonAttribute(EDigimonAttribute DigimonStage);
};
