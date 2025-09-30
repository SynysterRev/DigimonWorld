// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DigimonSubsystems.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonSubsystems : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	UFUNCTION(BlueprintPure, Category = "Subsystems", meta = (WorldContext = "WorldContextObject"))
	static T* GetSubsystem(const UObject* WorldContextObject)
	{
		if (!WorldContextObject) return nullptr;

		if (UWorld* World = WorldContextObject->GetWorld())
		{
			if (UGameInstance* GI = World->GetGameInstance())
			{
				return GI->GetSubsystem<T>();
			}
		}
		return nullptr;
	}
};
