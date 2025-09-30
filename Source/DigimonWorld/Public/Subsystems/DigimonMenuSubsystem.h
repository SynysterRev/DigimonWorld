// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUISubsystemBase.h"
#include "DigimonMenuSubsystem.generated.h"

class UDigimonTimeSubsystem;
class UCommonActivatableWidget;
class UDigimonMenuSettings;
DECLARE_LOG_CATEGORY_EXTERN(LogDigimonMenuSubsystem, Log, All);

class UMenuStack;

UCLASS()
class DIGIMONWORLD_API UDigimonMenuSubsystem : public UCommonUISubsystemBase
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void OpenPauseMenu();
	void ClosePauseMenu();
	void OpenMenu(const FName& MenuName);

private:
	
	UPROPERTY(Transient)
	TObjectPtr<UMenuStack> MenuStackWidget = nullptr;

	UPROPERTY(Transient)
	TObjectPtr<UDigimonMenuSettings> MenuSettings = nullptr;

	UPROPERTY(Transient)
	TMap<FName, UCommonActivatableWidget*> MenuInstances;

	UCommonActivatableWidget* GetOrCreateMenu(FName MenuName);

	UMenuStack* GetOrCreateMenuStack();	
};
