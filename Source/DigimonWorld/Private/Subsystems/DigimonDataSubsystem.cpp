// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/DigimonDataSubsystem.h"

#include "Data/DigimonGlobalData.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Settings/DigimonSettings.h"

DEFINE_LOG_CATEGORY(LogDigimonDataSubsystem);

void UDigimonDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const UDigimonSettings* Settings = UDigimonSettings::GetDigimonWorldSettings())
	{
		if (Settings->DigimonDataTable.IsNull())
		{
			UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonDataTable not referenced!"));
			return;
		}
		// FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		// StreamableManager.RequestAsyncLoad(
		// 	Settings->DigimonDataTable.ToSoftObjectPath(),
		// 	FStreamableDelegate::CreateUObject(this, &UDigimonDataSubsystem::OnDataTableLoaded)
		// );
		FSoftObjectPtr SoftObj(Settings->DigimonDataTable.ToSoftObjectPath());
		DigimonDataTable = Cast<UDataTable>(SoftObj.LoadSynchronous());
		UE_LOG(LogDigimonDataSubsystem, Log,TEXT("DigimonDataTable loaded from settings successfully"));

		if (Settings->DigimonGlobalsData.IsNull())
		{
			UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonGlobalsData not referenced!"));
			return;
		}
		FSoftObjectPtr GlobalDataSoftObj(Settings->DigimonGlobalsData.ToSoftObjectPath());
		DigimonGlobalsData = Cast<UDigimonGlobalsData>(GlobalDataSoftObj.LoadSynchronous());
		
	}
}

bool UDigimonDataSubsystem::GetPartnerDigimonStats(const FName DigimonID, FDigimonPartnerData& OutPartnerData) const
{
	if (!DigimonDataTable)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonDataTable not loaded yet!"));
		return false;
	}
	const FString Context;
	// UE_LOG(LogTemp, Warning, TEXT("RowStruct: %s"), *DigimonDataTable->RowStruct->GetName());
	FDigimonPartnerData* PartnerData = DigimonDataTable->FindRow<FDigimonPartnerData>(DigimonID, Context);
	if (!PartnerData)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("Can't find data for digimon with ID '%s' in partner table"), *DigimonID.ToString());
		return false;
	}
	OutPartnerData = *PartnerData;
	return true;
}

void UDigimonDataSubsystem::LogAllPartnerRows() const
{
	if (!DigimonDataTable)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonDataTable is nullptr!"));
		return;
	}

	UE_LOG(LogDigimonDataSubsystem, Log, TEXT("=== Listing all rows in %s ==="), *DigimonDataTable->GetName());

	for (const FName& RowName : DigimonDataTable->GetRowNames())
	{
		UE_LOG(LogDigimonDataSubsystem, Log, TEXT(" - RowName: %s"), *RowName.ToString());
	}

	UE_LOG(LogDigimonDataSubsystem, Log, TEXT("=== End of row list ==="));
}

bool UDigimonDataSubsystem::GetEnemyDigimonStats(const FName DigimonID, FDigimonEnemyData& OutEnemyData) const
{
	if (!DigimonDataTable)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonDataTable not loaded yet!"));
		return false;
	}
	const FString Context;
	FDigimonEnemyData* EnemyData = DigimonDataTable->FindRow<FDigimonEnemyData>(DigimonID, Context);
	if (!EnemyData)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("'%s' Can't find data for digimon with ID in enemy table"), *DigimonID.ToString());
		return false;
	}
	OutEnemyData = *EnemyData;
	return true;
}

UDigimonGlobalsData* UDigimonDataSubsystem::GetDigimonGlobalsData() const
{
	if (!DigimonGlobalsData)
	{
		UE_LOG(LogDigimonDataSubsystem, Error, TEXT("DigimonGlobalsData is nullptr!"));
		return nullptr;
	}
	return DigimonGlobalsData;
}

void UDigimonDataSubsystem::OnDataTableLoaded()
{
	if (const UDigimonSettings* GameSettings = UDigimonSettings::GetDigimonWorldSettings())
	{
		DigimonDataTable = GameSettings->DigimonDataTable.Get();
    
		if (DigimonDataTable)
		{
			UE_LOG(LogDigimonDataSubsystem, Log, TEXT("DigimonDataTable loaded from settings successfully"));
		}
	}
}
