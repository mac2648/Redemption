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
#include "HealthBarWidget.h"

#define POWER_UP_ACTION PowerUpComp->GetUsePowerAction()

ARedemptionPlayer::ARedemptionPlayer()
{
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Comp"));
	PrimaryActorTick.bCanEverTick = true;
	// Stamina settings
	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	MaxSprintSpeed = 600.0f; // How fast you run
	StaminaDepletionRate = 75.0f; // per second while sprinting
	StaminaRegenerationRate = 15.0f; // per second while not sprinting
	bCanSprint = true;


	if (UWidgetComponent* WidgetComponent = HealthComp->GetWidgetComp())
	{
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(defs::HealthBarZ);
		static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass{ TEXT("/Game/UI/BP_HealthBar") };
		if (WidgetClass.Succeeded())
		{
			WidgetComponent->SetWidgetClass((WidgetClass.Class));
		}
		static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionFinder(TEXT("/Game/Player/Input/Actions/IA_Sprint"));
		if (SprintActionFinder.Succeeded())
		{
			SprintAction = SprintActionFinder.Object;
			UE_LOG(LogTemp, Warning, TEXT("BINDED AND FOUND"));
		}

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
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			Subsystem->AddMappingContext(TPPMappingContext, 1);
		}
	}
	// Creating the stamina widget for the hud
	if (StaminaWidgetClass != nullptr)
	{
		StaminaWidget = CreateWidget<UUserWidget>(GetWorld(), StaminaWidgetClass);
		if (StaminaWidget != nullptr)
		{
			StaminaWidget->AddToViewport();
		}
	}
}

// Called every frame
void ARedemptionPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsSprinting && bCanSprint)
	{
		Stamina -= StaminaDepletionRate * DeltaTime;
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

	// Update the HUD with the new stamina value
	UpdateStaminaWidget(Stamina / MaxStamina);
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
		}
		else
		{
			UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 0.5f, this);
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
}

void ARedemptionPlayer::EndCrouch()
{
	ACharacter::UnCrouch();

	FVector offset = FVector(0, 0, 40);
	FPPCamera->AddWorldOffset(offset);

	GetCapsuleComponent()->SetCapsuleSize(42.f, 96.0f);
}

void ARedemptionPlayer::StartSprinting()
{
	UE_LOG(LogTemp, Warning, TEXT("StartSprinting called"));
	if (Stamina > 0 && bCanSprint)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
	}
}

void ARedemptionPlayer::StopSprinting()
{
	UE_LOG(LogTemp, Warning, TEXT("StopSprinting called"));
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 250.f;
}

void ARedemptionPlayer::UpdateStaminaWidget(float StamPercent)
{
	// Will affect the HUD elements eventually.
}
