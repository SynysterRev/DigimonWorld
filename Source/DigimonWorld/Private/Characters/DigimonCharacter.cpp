// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DigimonCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/DigimonStatsComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/Digimons/DigimonBubbleIndicatorWidget.h"

DEFINE_LOG_CATEGORY(LogDigimonCharacter);

// Sets default values
ADigimonCharacter::ADigimonCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StatsComponent = CreateDefaultSubobject<UDigimonStatsComponent>("Stats Component");
	BubbleIndicatorWidget = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	BubbleIndicatorWidget->SetupAttachment(RootComponent);
	BubbleIndicatorWidget->SetDrawSize(FVector2D(64, 64));
}

// Called when the game starts or when spawned
void ADigimonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADigimonCharacter::ChangeMesh(USkeletalMesh* NewMesh)
{
	if (USkeletalMeshComponent* SkeletalMeshComponent = GetMesh())
	{
		SkeletalMeshComponent->SetSkeletalMesh(NewMesh);
	}
	AdjustCollisionAndUI();
}

void ADigimonCharacter::AdjustCollisionAndUI()
{
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	if (!CapsuleComp) return;

	if (USkeletalMesh* CurrentMesh = GetMesh()->GetSkeletalMeshAsset())
	{
		FBoxSphereBounds Bounds = CurrentMesh->GetBounds();

		float MeshHeight = Bounds.BoxExtent.Z * 2.0f;
		float MeshRadius = FMath::Max(Bounds.BoxExtent.X, Bounds.BoxExtent.Y);
		CapsuleComp->SetCapsuleRadius(MeshRadius * 0.5f);
		CapsuleComp->SetCapsuleHalfHeight(MeshHeight * 0.5f);

		float CapsuleHalfHeight = CapsuleComp->GetUnscaledCapsuleHalfHeight();
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -CapsuleHalfHeight));

		if (BubbleIndicatorWidget)
		{
			float WidgetHeight = CapsuleHalfHeight;
			BubbleIndicatorWidget->SetRelativeLocation(FVector(0, 0, WidgetHeight));
		}

		// OnMeshDimensionsChanged.Broadcast(MeshHeight, MeshRadius);
	}
}

void ADigimonCharacter::InitializeBaseData(const FDigimonBaseData& BaseData)
{
	DigimonStage = BaseData.DigimonStage;
	DisplayName = BaseData.DisplayName;
	DigimonAttribute = BaseData.DigimonAttribute;
	StatsComponent->InitializeStats(BaseData.DigimonStats);
	ChangeMesh(BaseData.SkeletalMesh.Get());
}

// Called every frame
void ADigimonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADigimonCharacter::InitializeDigimon(const FName& InDigimonID, UDigimonDataSubsystem* DataSubsystem)
{
	DigimonID = InDigimonID;
	if (!StatsComponent)
	{
		UE_LOG(LogDigimonCharacter, Error, TEXT("No stats component created in the digimon"));
		return;
	}
	if (!DataSubsystem)
	{
		UE_LOG(LogDigimonCharacter, Error, TEXT("Can't find digimon data subsystem"));
		return;
	}
}

void ADigimonCharacter::AddNewBubbleIndicator(EDigimonBubbleType BubbleType)
{
	if (!BubbleIndicatorWidget) return;
	if (UDigimonBubbleIndicatorWidget* IndicatorWidget = Cast<UDigimonBubbleIndicatorWidget>(
		BubbleIndicatorWidget->GetWidget()))
	{
		IndicatorWidget->AddBubbleType(BubbleType);
	}
}

void ADigimonCharacter::RemoveBubbleIndicator(EDigimonBubbleType BubbleType)
{
	if (!BubbleIndicatorWidget) return;
	if (UDigimonBubbleIndicatorWidget* IndicatorWidget = Cast<UDigimonBubbleIndicatorWidget>(
		BubbleIndicatorWidget->GetWidget()))
	{
		IndicatorWidget->RemoveBubbleType(BubbleType);
	}
}
