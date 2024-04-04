// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleLever.h"
#include "InteractWidgetComponent.h"
#include "Sound/SoundCue.h"
#include <Kismet/GameplayStatics.h>

APuzzleLever::APuzzleLever()
{
	PrimaryActorTick.bCanEverTick = true;
	InteractComp = CreateDefaultSubobject<UInteractWidgetComponent>(TEXT("Interact Comp"));

	SetRootComponent(BaseMesh);

	PuzzleMesh->SetupAttachment(BaseMesh);
}

void APuzzleLever::Activate()
{
	IsActive = !IsActive;

	IsRotating = true;

	OnActivate.Broadcast();
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), SwitchCue, GetActorLocation());
	ShowSequence();
}

void APuzzleLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		FRotator RotationRate;
		FRotator DesiredRot;

		if (IsActive)
		{
			RotationRate = FRotator(-80, 0, 0);
			DesiredRot = FRotator(-40, 0, 0);
		}
		else
		{
			RotationRate = FRotator(80, 0, 0);
			DesiredRot = FRotator(40, 0, 0);
		}

		PuzzleMesh->AddLocalRotation(RotationRate * DeltaTime);

		FRotator PuzzleMeshRot = PuzzleMesh->GetRelativeRotation();
		
		if ((PuzzleMeshRot - DesiredRot).IsNearlyZero(1))
		{
			IsRotating = false;
		}
	}
}
