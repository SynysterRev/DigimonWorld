// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DigimonAIController.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API ADigimonAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADigimonAIController();

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComponentComponent = nullptr;
	
};
