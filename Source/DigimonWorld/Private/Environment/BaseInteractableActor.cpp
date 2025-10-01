// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/BaseInteractableActor.h"

#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseInteractableActor::ABaseInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	// RootComponent = Collider;
	MeshComponent->SetupAttachment(Collider);
}

// Called when the game starts or when spawned
void ABaseInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseInteractableActor::OnInteracted_Implementation(AActor* Interactor)
{
}

// Called every frame
void ABaseInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseInteractableActor::CanInteract_Implementation(AActor* Interactor) const
{
	return bCanBeInteracted;
}

void ABaseInteractableActor::Interact_Implementation(AActor* Interactor)
{
	if (CanInteract_Implementation(Interactor))
	{
		// PlayInteractionFeedback();
		OnInteracted(Interactor);
	}
}

void ABaseInteractableActor::SetInteractable(bool bCanInteract)
{
	bCanBeInteracted = bCanInteract;
}

