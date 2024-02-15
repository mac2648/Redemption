// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Bone.h"
#include "GameFramework/Character.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())

const int BONE_SPEED = 5000;

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

	// ...
}

void UPowerUpComponent::UsePowerUp(const FInputActionValue& Value)
{
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
	if (BoneBP)
	{
		if (ACharacter* OwnerChar = Cast<ACharacter>(GetOwner()))
		{
			FVector FowardVec = OwnerChar->GetActorForwardVector();
			FVector SpawnPos = OwnerChar->GetActorLocation() + FowardVec * 100;

			FRotator CharacterRotation = FowardVec.Rotation();

			FVector BoneDirection = FowardVec + FVector(0.0, 0.0, 0.3);

			ABone* Bone = GetWorld()->SpawnActor<ABone>(BoneBP, SpawnPos, FRotator::ZeroRotator);
			Bone->GetMesh()->AddImpulse(BoneDirection * BONE_SPEED);
		}
	}
}