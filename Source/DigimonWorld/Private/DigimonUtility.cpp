// Fill out your copyright notice in the Description page of Project Settings.


#include "DigimonUtility.h"

#include "Utilities/DigimonStringTableManager.h"

FText FDigimonUtility::GetTextForDigimonStage(EDigimonStage DigimonStage)
{
	FString EnumName = StaticEnum<EDigimonStage>()->GetNameStringByValue(static_cast<int64>(DigimonStage));

	return UDigimonStringTableManager::Get()->GetText(TEXT("DigimonInfo"), FName(*EnumName));
}

FText FDigimonUtility::GetTextForDigimonAttribute(EDigimonAttribute DigimonStage)
{
	FString EnumName = StaticEnum<EDigimonAttribute>()->GetNameStringByValue(static_cast<int64>(DigimonStage));
	
	return UDigimonStringTableManager::Get()->GetText(TEXT("DigimonInfo"), FName(*EnumName));
}
