// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DigimonStringTableManager.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonStringTableManager : public UObject
{
	GENERATED_BODY()

public:
	static UDigimonStringTableManager* Get();
    
	UStringTable* GetStringTable(const FName& TableName);
    
	FText GetText(const FName& TableName, const FName& Key);

private:

	UPROPERTY()
	TMap<FName, UStringTable*> LoadedStringTables;
    
	static const TMap<FName, FString> StringTablePaths;
};
