// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Toilet.generated.h"

class UBoxComponent;

UCLASS()
class DIGIMONWORLD_API AToilet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToilet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	void OnTriggerOverlapped(UPrimitiveComponent* OverlappedComponent,
								  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
								  bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

public:	

};
