// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractionComponent.h"

#include "Interfaces/Interactable.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	CurrentInteractable = nullptr;
	InteractionProgress = 0.0f;
}


void UInteractionComponent::StartInteraction()
{
	if (!CurrentInteractable) return;

	if (IInteractable::Execute_CanInteract(CurrentInteractable, GetOwner()))
	{
		IInteractable::Execute_Interact(CurrentInteractable, GetOwner());
	}
}

// void UInteractionComponent::StopInteraction()
// {
// }

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckForInteractables();
}

void UInteractionComponent::CheckForInteractables()
{
	AActor* BestInteractable = FindBestInteractable();

	if (BestInteractable != CurrentInteractable)
	{
		if (CurrentInteractable)
		{
			OnInteractableLost.Broadcast();
		}

		CurrentInteractable = BestInteractable;

		if (CurrentInteractable)
		{
			OnInteractableFound.Broadcast(CurrentInteractable);
		}
	}
}

AActor* UInteractionComponent::FindBestInteractable() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return nullptr;

	FVector Start = OwnerPawn->GetActorLocation();
	FVector Forward = OwnerPawn->GetActorForwardVector();
	FVector End = Start + (Forward * InteractionRange);

	// Sphere trace pour trouver les interactables
	TArray<FHitResult> HitResults;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(50.0f),
		QueryParams
	);

	AActor* BestActor = nullptr;
	float BestDistance = InteractionRange;

	for (const FHitResult& Hit : HitResults)
	{
		AActor* HitActor = Hit.GetActor();
		if (HitActor && HitActor->Implements<UInteractable>())
		{
			if (IInteractable::Execute_CanInteract(HitActor, GetOwner()))
			{
				float Distance = FVector::Dist(Start, Hit.Location);
				if (Distance < BestDistance)
				{
					BestDistance = Distance;
					BestActor = HitActor;
				}
			}
		}
	}

	return BestActor;
}
