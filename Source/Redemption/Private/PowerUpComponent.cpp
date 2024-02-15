// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bone.h"
#include "RedemptionPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}


// Called every frame
void UPowerUpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (BoneCD >= 0)
	{
		BoneCD -= DeltaTime;
	}
}

void UPowerUpComponent::UsePowerUp(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Using Power"));
	
	if (CurrentPowerUp == EActivePowerUp::BoneThrow)
	{
		ExecuteBonePowerUp();
	}
	else if (CurrentPowerUp == EActivePowerUp::Hover)
	{
		UE_LOG(LogTemp, Warning, TEXT("HOVER!!!!!!"))
	}
	else if (CurrentPowerUp == EActivePowerUp::Parry)
	{
		UE_LOG(LogTemp, Warning, TEXT("PARRY!!!!!!"))
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
			Subsystem->AddMappingContext(HoverMappingContext, 0);
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

			UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerChar->GetCharacterMovement()->Velocity.ToString());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(BoneDirection * BONE_SPEED).ToString());
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(BoneDirection * BONE_SPEED + OwnerChar->GetCharacterMovement()->Velocity).ToString());

			ABone* Bone = GetWorld()->SpawnActor<ABone>(BoneBP, SpawnPos, CameraRotation);
			Bone->GetMesh()->SetPhysicsLinearVelocity(BoneDirection * BONE_SPEED + OwnerChar->GetCharacterMovement()->Velocity);

			BoneCD = BONE_CD;
		}
	}
}