// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bone.h"
#include "RedemptionPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ParryBarWidget.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())

const int BONE_SPEED = 550;

// Sets default values for this component's properties
UPowerUpComponent::UPowerUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPowerUpComponent::BeginPlay()
{
	Super::BeginPlay();

	ChangeMappingContext();
	Player = Cast<ARedemptionPlayer>(GetOwner());
}


// Called every frame
void UPowerUpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BoneCD >= 0)
	{
		BoneCD -= DeltaTime;
	}
	if (IsParrying)
	{
		ParryEnergy -= PARRY_DEPLETION_RATE * DeltaTime;
		if (ParryEnergy <= 0)
		{
			ExecuteParryPowerUp(false);
		}
	}
	else if (!IsParrying && ParryEnergy < PARRY_MAX_ENERGY)
	{
		ParryEnergy += PARRY_FILL_RATE * DeltaTime;
		if (ParryEnergy > PARRY_MAX_ENERGY)
		{
			ParryEnergy = PARRY_MAX_ENERGY;
		}
	}

	if (ParryBar)
	{
		if (ParryEnergy >= PARRY_MAX_ENERGY)
		{
			ParryBar->RemoveFromParent();
			ParryBar = nullptr;
		}
		else
		{
			ParryBar->SetBarValuePercent(GetParryEnergyPercentage());
		}
	}

	if (Player)
	{
		if (Player->CanJump()) // if player is on the ground
		{
			IsHovering = false;
			CanHover = true;
		}
	}

	if (IsHovering)
	{
		HoverEnergy -= PARRY_DEPLETION_RATE * DeltaTime;
		if (HoverEnergy <= 0)
		{
			IsHovering = false;
		}
		if (Player)
		{
			if (!Player->CanJump())
			{
				Player->GetCharacterMovement()->Velocity.Z = 0;
			}
		}
	}
	else
	{
		HoverEnergy = PARRY_MAX_ENERGY;
	}
}

void UPowerUpComponent::UsePowerUp(const FInputActionValue& Value)
{
	if (CurrentPowerUp == EActivePowerUp::BoneThrow)
	{
		ExecuteBonePowerUp();
	}
	else if (CurrentPowerUp == EActivePowerUp::Hover)
	{
		bool Hover = Value.Get<bool>();

		ExecuteHoverPowerUp(Hover);
	}
	else if (CurrentPowerUp == EActivePowerUp::Parry)
	{
		bool Parry = Value.Get<bool>();

		ExecuteParryPowerUp(Parry);
	}
}

void UPowerUpComponent::ChangeMappingContext()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM)
	{
		Subsystem->RemoveMappingContext(BoneMappingContext);
		Subsystem->RemoveMappingContext(HoverMappingContext);
		Subsystem->RemoveMappingContext(ParryMappingContext);

		if (CurrentPowerUp == EActivePowerUp::BoneThrow)
		{
			Subsystem->AddMappingContext(BoneMappingContext, 0);
		}

		if (CurrentPowerUp == EActivePowerUp::Hover)
		{
			Subsystem->AddMappingContext(HoverMappingContext, 3);
		}

		if (CurrentPowerUp == EActivePowerUp::Parry)
		{
			Subsystem->AddMappingContext(ParryMappingContext, 0);
		}
	}
}

void UPowerUpComponent::ChangeActivePowerUp(EActivePowerUp NewPower)
{
	CurrentPowerUp = NewPower;
	ChangeMappingContext();
}

//will spawn the bone
void UPowerUpComponent::ExecuteBonePowerUp()
{
	if (BoneBP && BoneCD <= 0.0)
	{
		if (ARedemptionPlayer* OwnerChar = Cast<ARedemptionPlayer>(GetOwner()))
		{
			FRotator CameraRotation = OwnerChar->GetControlRotation();

			FVector CameraVec = CameraRotation.Vector();

			FVector SpawnPos = OwnerChar->GetActorLocation() + CameraVec * 80 + FVector(0.0, 0.0, 50.0f);

			FVector BoneDirection = CameraVec + FVector(0.0, 0.0, 0.5);

			ABone* Bone = GetWorld()->SpawnActor<ABone>(BoneBP, SpawnPos, CameraRotation);
			Bone->GetMesh()->SetPhysicsLinearVelocity(BoneDirection * BONE_SPEED + OwnerChar->GetCharacterMovement()->Velocity);

			BoneCD = BONE_CD;
		}
	}
}

void UPowerUpComponent::ExecuteParryPowerUp(bool NewParry)
{
	IsParrying = NewParry;

	if (NewParry && !ParryBar)
	{
		ParryBar = CreateWidget<UParryBarWidget>(GetWorld(), ParryBarWidgetClass);
		if (ParryBar)
		{
			ParryBar->AddToViewport();
		}
	}
}

void UPowerUpComponent::ExecuteHoverPowerUp(bool NewHover)
{

	if (Player)
	{
		if (Player->CanJump())
		{
			Player->Jump();
		}
		else
		{
			if (CanHover && NewHover) //if trying to hover and can hover
			{
				IsHovering = NewHover;
				CanHover = false;
			}
			else if (!CanHover && !NewHover) //if cannot hover and trying to stop hovering
			{
				IsHovering = NewHover;
			}
		}

	}
}