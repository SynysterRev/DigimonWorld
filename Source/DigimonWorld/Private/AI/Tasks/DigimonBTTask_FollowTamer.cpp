// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/DigimonBTTask_FollowTamer.h"

#include "AI/DigimonAIController.h"
#include "Characters/PartnerDigimonCharacter.h"
#include "Characters/TamerCharacter.h"
#include "Navigation/PathFollowingComponent.h"

UDigimonBTTask_FollowTamer::UDigimonBTTask_FollowTamer()
{
	NodeName = TEXT("Follow Trainer");
}

EBTNodeResult::Type UDigimonBTTask_FollowTamer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ADigimonAIController* AIController = Cast<ADigimonAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
		return EBTNodeResult::Failed;

	APartnerDigimonCharacter* DigimonCharacter = Cast<APartnerDigimonCharacter>(AIController->GetPawn());
	if (!DigimonCharacter)
		return EBTNodeResult::Failed;

	FVector Location = DigimonCharacter->GetTamerCharacter()->GetActorLocation();
	auto result = AIController->MoveToLocation(Location, DistanceRadius);
	//AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, Location);
	if (result == EPathFollowingRequestResult::Type::Failed)
	{
		return EBTNodeResult::InProgress; //InProgress : continue task
	}
	return EBTNodeResult::Succeeded;
}

FString UDigimonBTTask_FollowTamer::GetStaticDescription() const
{
	return Super::GetStaticDescription();
}