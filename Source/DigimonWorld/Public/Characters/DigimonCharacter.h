// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/DigimonBaseData.h"
#include "DigimonCharacter.generated.h"

class UWidgetComponent;
class ATamerCharacter;
class UDigimonStatsComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogDigimonCharacter, Log, All);

UCLASS()
class DIGIMONWORLD_API ADigimonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADigimonCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ChangeMesh(USkeletalMesh* NewMesh);
	virtual void AdjustCollisionAndUI();
	virtual void InitializeBaseData(const FDigimonBaseData& BaseData);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FName DigimonID;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText DisplayName;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDigimonStatsComponent> StatsComponent = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> BubbleIndicatorWidget = nullptr;

	EDigimonStage DigimonStage;
	EDigimonAttribute DigimonAttribute;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitializeDigimon(const FName& InDigimonID, class UDigimonDataSubsystem* DataSubsystem);
	virtual void AddNewBubbleIndicator(EDigimonBubbleType BubbleType);
	virtual void RemoveBubbleIndicator(EDigimonBubbleType BubbleType);

	UFUNCTION(BlueprintPure, Category = "Digimon Info")
	EDigimonStage GetDigimonStage() const { return DigimonStage; }
    
	UFUNCTION(BlueprintPure, Category = "Digimon Info")
	EDigimonAttribute GetDigimonAttribute() const { return DigimonAttribute; }
};
