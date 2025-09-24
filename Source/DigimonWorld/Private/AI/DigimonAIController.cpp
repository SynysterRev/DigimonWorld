// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DigimonAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

ADigimonAIController::ADigimonAIController()
{
	BlackboardComponentComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void ADigimonAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree != nullptr)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

void ADigimonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (Blackboard != nullptr && BehaviorTree != nullptr)
	{
		InitializeBlackboard(*Blackboard, *BehaviorTree->BlackboardAsset);
	}
}