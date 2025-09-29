// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/DigimonStringTableManager.h"

#include "Internationalization/StringTable.h"

const TMap<FName, FString> UDigimonStringTableManager::StringTablePaths = {
    { TEXT("DigimonInfo"), TEXT("/Game/Localization/ST_Digimon_Info.ST_Digimon_Info") },
    { TEXT("DigimonNames"), TEXT("/Game/Localization/ST_Digimon_Names.ST_Digimon_Names") },
};

UDigimonStringTableManager* UDigimonStringTableManager::Get()
{
    static UDigimonStringTableManager* Instance = nullptr;
    
    if (!Instance)
    {
        Instance = NewObject<UDigimonStringTableManager>();
        Instance->AddToRoot();
    }
    
    return Instance;
}

UStringTable* UDigimonStringTableManager::GetStringTable(const FName& TableName)
{
    if (UStringTable** CachedTable = LoadedStringTables.Find(TableName))
    {
        if (*CachedTable)
        {
            return *CachedTable;
        }
    }
    
    const FString* PathPtr = StringTablePaths.Find(TableName);
    if (!PathPtr)
    {
        UE_LOG(LogTemp, Error, TEXT("String Table '%s' not found in paths"), *TableName.ToString());
        return nullptr;
    }
    
    FSoftObjectPath StringTablePath(*PathPtr);
    UStringTable* StringTable = Cast<UStringTable>(StringTablePath.TryLoad());
    
    if (!StringTable)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load String Table '%s' at path: %s"), 
            *TableName.ToString(), **PathPtr);
        return nullptr;
    }
    
    LoadedStringTables.Add(TableName, StringTable);
    
    UE_LOG(LogTemp, Log, TEXT("Successfully loaded String Table: %s"), *TableName.ToString());
    
    return StringTable;
}

FText UDigimonStringTableManager::GetText(const FName& TableName, const FName& Key)
{
    UStringTable* StringTable = GetStringTable(TableName);
    
    if (!StringTable)
    {
        return FText::FromString(FString::Printf(TEXT("[Missing: %s]"), *Key.ToString()));
    }
    
    return FText::FromStringTable(StringTable->GetStringTableId(), Key.ToString());
}