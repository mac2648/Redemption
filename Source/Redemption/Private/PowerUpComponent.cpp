// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUpComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Cast<APawn>(GetOwner())->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())

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
	UE_LOG(LogTemp, Warning, TEXT("Using Power"))
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