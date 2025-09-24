// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "DigimonBTTask_FollowTamer.generated.h"

/**
 * 
 */
UCLASS()
class DIGIMONWORLD_API UDigimonBTTask_FollowTamer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UDigimonBTTask_FollowTamer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DistanceRadius = 200.0f;

};
