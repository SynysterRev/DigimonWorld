// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/ToiletActor.h"

#include "Characters/TamerCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
AToiletActor::AToiletActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Trigger");
	RootComponent = BoxComponent;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Toilet Mesh");
	StaticMeshComponent->SetupAttachment(BoxComponent);
}

// Called when the game starts or when spawned
void AToiletActor::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AToiletActor::OnTriggerOverlapped);
}

void AToiletActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	BoxComponent->OnComponentBeginOverlap.RemoveDynamic(this, &AToiletActor::OnTriggerOverlapped);
	Super::EndPlay(EndPlayReason);
}

void AToiletActor::OnTriggerOverlapped(UPrimitiveComponent* OverlappedComponent,
                                  AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                  bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
		return;
	if (ATamerCharacter* Tamer = Cast<ATamerCharacter>(OtherActor))
	{
		Tamer->TryUseToilet();
	}
}
