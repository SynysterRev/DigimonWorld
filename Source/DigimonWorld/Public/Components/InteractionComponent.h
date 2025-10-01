// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableFound, AActor*, InteractableActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractableLost);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIGIMONWORLD_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckFrequency = 0.1f;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableFound OnInteractableFound;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractableLost OnInteractableLost;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StartInteraction();

	// UFUNCTION(BlueprintCallable, Category = "Interaction")
	// void StopInteraction();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	AActor* GetCurrentInteractable() const { return CurrentInteractable; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	AActor* CurrentInteractable;

	FTimerHandle InteractionTimerHandle;
	float InteractionProgress;

	void CheckForInteractables();
	AActor* FindBestInteractable() const;
};
