// Fill out your copyright notice in the Description page of Project Settings.

#include "RedemptionPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "PowerUpComponent.h"
#include "Components/WidgetComponent.h"
#include "HealthComponent.h"
#include "PauseMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "StaminaBarWidget.h"
#include "Sound/SoundCue.h"



#define POWER_UP_ACTION PowerUpComp->GetUsePowerAction()
#define SPRINT_STEP_TIMER 0.15
#define WALK_STEP_TIMER 0.8
#define CROUCH_STEP_TIMER 0.9


ARedemptionPlayer::ARedemptionPlayer()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
	PrimaryActorTick.bCanEverTick = true;
	// Stamina settings
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	MaxSprintSpeed = 450.0f; // How fast you run
	StaminaDepletionRate = 65.0f; // per second while sprinting
	StaminaRegenerationRate = 15.0f; // per second while not sprinting
	bCanSprint = true;

	static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionFinder(TEXT("/Game/Player/Input/Actions/IA_Sprint"));
	if (SprintActionFinder.Succeeded())
	{
		SprintAction = SprintActionFinder.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundCue> SoundActionFinder(TEXT("/Game/Assets/Sounds/Characters/Player/Steps"));
	if (SprintActionFinder.Succeeded())
	{
		FootStepsCue = SoundActionFinder.Object;
	}

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	TPPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPPCamera"));
	TPPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TPPCamera->bUsePawnControlRotation = false;

	FPPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPPCamera"));
	FPPCamera->SetupAttachment(ACharacter::GetMesh());
	FPPCamera->bUsePawnControlRotation = true;

	PowerUpComp = CreateDefaultSubobject<UPowerUpComponent>(TEXT("PowerUpComp"));
}

void ARedemptionPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
			Subsystem->AddMappingContext(TPPMappingContext, 2);
		}
	}
	// Creating the stamina widget for the hud
	if (StaminaWidgetClass != nullptr)
	{
		StaminaWidget = CreateWidget<UStaminaBarWidget>(GetWorld(), StaminaWidgetClass);
		if (StaminaWidget != nullptr)
		{
			StaminaWidget->AddToViewport();
		}
	}

	if (NoiseWidgetClass != nullptr)
	{
		UUserWidget* NoiseWidget = CreateWidget<UUserWidget>(GetWorld(), NoiseWidgetClass);

		if (NoiseWidget != nullptr)
		{
			NoiseWidget->AddToViewport();
		}
	}
}

// Called every frame
void ARedemptionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FallNoiseFrames > 0)
	{
		FallNoiseFrames--;
	}

	TickSprint(DeltaTime);
	TickStamina();
	TickNoiseReporting();
}

void ARedemptionPlayer::TickSprint(float DeltaTime)
{
	if (bIsSprinting && bCanSprint)
	{
		if (CanJump())
		{
			Stamina -= StaminaDepletionRate * DeltaTime;
		}

		if (Stamina <= 0)
		{
			Stamina = 0;
			StopSprinting(); // prevent sprinting when stamina is depleted
			bCanSprint = false; // Disable sprinting
		}
	}
	else
	{
		Stamina += StaminaRegenerationRate * DeltaTime;
		if (Stamina >= MaxStamina)
		{
			Stamina = MaxStamina;
			bCanSprint = true; // Enable sprinting
		}
	}
}

void ARedemptionPlayer::TickStamina()
{
	// Update the HUD with the new stamina value
	UpdateStaminaWidget(Stamina / MaxStamina);
	// Show/hide the stamina widget based on sprinting and stamina value
	if (bIsSprinting || Stamina != MaxStamina)
	{
		// Show
		StaminaWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		// Hide
		StaminaWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void ARedemptionPlayer::TickNoiseReporting()
{
	if (GetCharacterMovement()->Velocity == FVector::ZeroVector)
	{
		GetWorld()->GetTimerManager().ClearTimer(FootStepsHandle);
		if (FallNoiseFrames <= 0)
		{
			PlayerNoise = 0;
		}
	}

	if (!FallNoiseHandle.IsValid() && !CanJump())
	{
		GetWorld()->GetTimerManager().SetTimer(FallNoiseHandle, this, &ARedemptionPlayer::NotifyAIOfFall, 0.03, true);
	}
}

// Called to bind functionality to input
void ARedemptionPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARedemptionPlayer::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARedemptionPlayer::Look);

		EnhancedInputComponent->BindAction(POWER_UP_ACTION, ETriggerEvent::Triggered, PowerUpComp, &UPowerUpComponent::UsePowerUp);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ARedemptionPlayer::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ARedemptionPlayer::EndCrouch);

		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ARedemptionPlayer::StartSprinting);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ARedemptionPlayer::StopSprinting);

		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ARedemptionPlayer::LauchPauseMenu);
	}
}

void ARedemptionPlayer::Move(const FInputActionValue& Value)
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

		if (bIsCrouched)
		{
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 0.25f, this);
			PlayerNoise = 0.25;
		}
		else if (bIsSprinting)
		{
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);
			PlayerNoise = 1;
		}
		else
		{
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 0.5f, this);
			PlayerNoise = 0.5;
		}

		if (!FootStepsHandle.IsValid())
		{
			if (bIsCrouched)
			{
				StepVolume = 0.35;
				GetWorld()->GetTimerManager().SetTimer(FootStepsHandle, this, &ARedemptionPlayer::StepSound, CROUCH_STEP_TIMER, true);
			}
			else if (bIsSprinting)
			{
				StepVolume = 1.5;
				GetWorld()->GetTimerManager().SetTimer(FootStepsHandle, this, &ARedemptionPlayer::StepSound, SPRINT_STEP_TIMER, true);
			}
			else
			{
				StepVolume = 0.75;
				GetWorld()->GetTimerManager().SetTimer(FootStepsHandle, this, &ARedemptionPlayer::StepSound, WALK_STEP_TIMER, true);
			}
		}
	}
}

void ARedemptionPlayer::Look(const FInputActionValue& Value)
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

void ARedemptionPlayer::StartCrouch()
{
	ACharacter::Crouch();

	FVector offset = FVector(0, 0, -40);
	FPPCamera->AddWorldOffset(offset);

	GetCapsuleComponent()->SetCapsuleSize(42.f, 60.0f);

	GetWorld()->GetTimerManager().ClearTimer(FootStepsHandle);
}

void ARedemptionPlayer::EndCrouch()
{
	ACharacter::UnCrouch();

	FVector offset = FVector(0, 0, 40);
	FPPCamera->AddWorldOffset(offset);

	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.0f);
	GetWorld()->GetTimerManager().ClearTimer(FootStepsHandle);
}

void ARedemptionPlayer::StartSprinting()
{
	if (CanJump())
	{
		if (Stamina > 0 && bCanSprint)
		{
			bIsSprinting = true;
			GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
			GetWorld()->GetTimerManager().ClearTimer(FootStepsHandle);
		}
	}
}

void ARedemptionPlayer::StopSprinting()
{
	if (CanJump())
	{
		if (bIsSprinting)
		{
			GetWorld()->GetTimerManager().ClearTimer(FootStepsHandle);
		}

		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 250.f;
	}
	else
	{
		NeedToStopSprinting = true;
	}
}

void ARedemptionPlayer::UpdateStaminaWidget(float StamPercent)
{
	StaminaWidget->SetBarValuePercent(StamPercent);
	// Will affect the HUD elements eventually.
}

void ARedemptionPlayer::LauchPauseMenu()
{
	UPauseMenuWidget* UserInterface = CreateWidget<UPauseMenuWidget>(GetWorld(), PauseWidgetClass);
	UserInterface->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->bShowMouseCursor = true;
	
}

void ARedemptionPlayer::StepSound()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepsCue, GetActorLocation(), StepVolume);
}

void ARedemptionPlayer::NotifyAIOfFall()
{
	//if player arrives in the ground
	if (CanJump())
	{
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 0.8f, this);
		PlayerNoise = 0.8;
		GetWorld()->GetTimerManager().ClearTimer(FallNoiseHandle);
		FallNoiseFrames = 12;

		if (NeedToStopSprinting)
		{
			StopSprinting();
			NeedToStopSprinting = false;
		}
	}
}