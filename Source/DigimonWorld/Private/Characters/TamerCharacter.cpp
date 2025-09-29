// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/TamerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Characters/PartnerDigimonCharacter.h"
#include "Components/DigimonLifeComponent.h"
#include "Components/DigimonNeedsComponent.h"
#include "Subsystems/DigimonDataSubsystem.h"
#include "Subsystems/DigimonTimeSubsystem.h"
#include "Subsystems/DigimonUISubsystem.h"

DEFINE_LOG_CATEGORY(LogTamerCharacter);

// Sets default values
ATamerCharacter::ATamerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ATamerCharacter::TryUseToilet()
{
	if (!CurrentDigimon)
		return;

	if (CurrentDigimon->NeedToUseToilet())
	{
		CurrentDigimon->UseToilet();
		UGameInstance* GameInstance = GetGameInstance();
		if (!GameInstance)
		{
			OnUseToiletEnd();
			return;
		}
		if (UDigimonUISubsystem* UISubsystem = GameInstance->GetSubsystem<UDigimonUISubsystem>())
		{
			UISubsystem->ShowToiletSign();
			UISubsystem->OnToiletSignAnimationEnd.AddDynamic(this, &ATamerCharacter::OnUseToiletEnd);
			DisableCharacterInputs();
		}
		if (UDigimonTimeSubsystem* TimeSubsystem = GameInstance->GetSubsystem<UDigimonTimeSubsystem>())
		{
			TimeSubsystem->PauseTime();
		}
	}
}

void ATamerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (DigimonClass == nullptr)
	{
		UE_LOG(LogTamerCharacter, Error, TEXT("No digimon class referenced in the Tamer"));
		return;
	}
	if (UWorld* World = GetWorld())
	{
		FVector StartLine = GetActorLocation() + -GetActorForwardVector() * 200.0f;
		FVector EndLine = StartLine + FVector::DownVector * 150.0f;
		FHitResult HitResult;
		if (World->LineTraceSingleByChannel(HitResult, StartLine, EndLine, ECollisionChannel::ECC_WorldStatic))
		{
			float HalfHeight;
			float Radius;
			DigimonClass.GetDefaultObject()->GetCapsuleComponent()->GetScaledCapsuleSize(Radius, HalfHeight);

			FVector SpawnLocation = HitResult.ImpactPoint + FVector::UpVector * HalfHeight;
			FRotator Rotation = GetActorRotation();
			FActorSpawnParameters SpawnParams;

			FTransform TransformSpawn;
			TransformSpawn.SetLocation(SpawnLocation);
			TransformSpawn.SetRotation(Rotation.Quaternion());
			CurrentDigimon = World->SpawnActorDeferred<APartnerDigimonCharacter>(DigimonClass, TransformSpawn);
			//CurrentPokemon = World->SpawnActor<APokemonCharacter>(CurrentPokemonClass, SpawnLocation, Rotation, SpawnParams);
			if (CurrentDigimon)
			{
				CurrentDigimon->AssignTamer(this);
				if (UGameInstance* GameInstance = World->GetGameInstance())
				{
					if (UDigimonDataSubsystem* DataSubsystem = GameInstance->GetSubsystem<UDigimonDataSubsystem>())
					{
						CurrentDigimon->InitializeDigimon("Agumon", DataSubsystem);
						DataSubsystem->SetDigimonCharacter(CurrentDigimon);
					}
				}
				CurrentDigimon->FinishSpawning(TransformSpawn);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ATamerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATamerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATamerCharacter::Look);
		EnhancedInputComponent->BindAction(FeedAction, ETriggerEvent::Started, this, &ATamerCharacter::Feed);
	}
	else
	{
		UE_LOG(LogTamerCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATamerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ATamerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATamerCharacter::Feed(const FInputActionValue& Value)
{
	if (!CurrentDigimon) return;

	CurrentDigimon->TryConsumeItem();
	if (UDigimonNeedsComponent* NeedsComponent = CurrentDigimon->GetDigimonNeedsComponent())
	{
		
	}
	if (UDigimonLifeComponent* LifeComponent = CurrentDigimon->GetDigimonLifeComponent())
	{
		
	}
}

void ATamerCharacter::OnUseToiletEnd()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!GameInstance)
	{
		EnableCharacterInputs();
		return;
	}
	if (UDigimonUISubsystem* UISubsystem = GameInstance->GetSubsystem<UDigimonUISubsystem>())
	{
		UISubsystem->OnToiletSignAnimationEnd.RemoveDynamic(this, &ATamerCharacter::OnUseToiletEnd);
		EnableCharacterInputs();
	}
	if (UDigimonTimeSubsystem* TimeSubsystem = GameInstance->GetSubsystem<UDigimonTimeSubsystem>())
	{
		TimeSubsystem->ResumeTime();
	}
}

void ATamerCharacter::DisableCharacterInputs()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		DisableInput(PC);
	}
}

void ATamerCharacter::EnableCharacterInputs()
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		EnableInput(PC);
	}
}

