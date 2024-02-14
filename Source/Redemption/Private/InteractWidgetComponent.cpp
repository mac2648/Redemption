// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractWidgetComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "RedemptionPlayer.h"
#include "PuzzleLever.h"

#define GET_PLAYER_CONTROLLER Cast<APlayerController>(Player->GetController())
#define GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GET_PLAYER_CONTROLLER->GetLocalPlayer())

// Sets default values for this component's properties
UInteractWidgetComponent::UInteractWidgetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("box comp"));
}


// Called when the game starts
void UInteractWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UInteractWidgetComponent::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &UInteractWidgetComponent::OnOverlapEnd);
	BoxComp->SetWorldLocation(GetOwner()->GetActorLocation());
}

void UInteractWidgetComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(OtherActor))
	{
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(Player->InputComponent))
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &UInteractWidgetComponent::Interract);
		}

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM)
		{
			Subsystem->AddMappingContext(InteractMappingContext, 0);

		}

		if (InteractWidgetClass && !InteractWidget)
		{
			InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractWidgetClass);
			InteractWidget->AddToViewport();
		}
	}
}

void UInteractWidgetComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(OtherActor))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = GET_ENHANCED_INPUT_LOCAL_PLAYER_SUBSYSTEM)
		{
			Subsystem->RemoveMappingContext(InteractMappingContext);
		}

		if (InteractWidget)
		{
			InteractWidget->RemoveFromParent();
			InteractWidget = nullptr;
		}
	}
}

void UInteractWidgetComponent::Interract()
{
	if (APuzzleLever* Lever = Cast<APuzzleLever>(GetOwner()))
	{
		Lever->Activate();
	}
}