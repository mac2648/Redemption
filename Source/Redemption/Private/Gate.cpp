// Fill out your copyright notice in the Description page of Project Settings.

#include "Gate.h"
#include "Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Math.h"

#define ROTATION_INTERVAL 0.005
#define DOOR_SPEED 180

// Sets default values
AGate::AGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AGate::BeginPlay()
{
	Super::BeginPlay();

	TArray<AInteractable*> InteractObjs;
	InteractableKeys.GetKeys(InteractObjs);

	for (AInteractable* Current : InteractObjs)
	{
		//subscribe to all OnActivate events from the keys
		Current->OnActivate.AddDynamic(this, &AGate::CheckOpenConditions);
	}

	if (MasterKey)
	{
		MasterKey->OnActivate.AddDynamic(this, &AGate::CheckOpenConditions);
	}

	ClosedRotation = GetActorRotation();
	OpenedRotation = GetActorRotation();
	OpenedRotation.Yaw += MoveAngle;
}

void AGate::CheckOpenConditions()
{
	bool ShouldOpen = true;

	TArray<AInteractable*> InteractObjs;
	InteractableKeys.GetKeys(InteractObjs);

	TArray<bool> TriggerValue;
	InteractableKeys.GenerateValueArray(TriggerValue);

	for (int i = 0; i < InteractObjs.Num(); i++)
	{
		if (!(InteractObjs[i]->GetIsActive() == TriggerValue[i]))
		{
			ShouldOpen = false;
			break;
		}
	}

	if (MasterKey)
	{
		if (MasterKey->GetIsActive())
		{
			ShouldOpen = true;
		}
	}

	if (ShouldOpen && !IsOpen)
	{
		UGameplayStatics::SpawnSound2D(this, DoorOpenSoundBase, 0.7f);
		IsOpen = true;
		FTimerHandle RotationHandle;
		GetWorld()->GetTimerManager().SetTimer(RotationHandle, this, &AGate::RotateGate, ROTATION_INTERVAL, false);
	}
	else if (!ShouldOpen && IsOpen)
	{
		UGameplayStatics::SpawnSound2D(this, DoorCloseSoundBase, 0.7f);
		IsOpen = false;
		FTimerHandle RotationHandle;
		GetWorld()->GetTimerManager().SetTimer(RotationHandle, this, &AGate::RotateGate, ROTATION_INTERVAL, false);
	}
}

void AGate::RotateGate()
{
	FRotator CurrentRotation = GetActorRotation();

	if (IsOpen)
	{
		if ((CurrentRotation - OpenedRotation).IsNearlyZero(0.001))
		{
			return;
		}

		FRotator NewRotation = Math::InterpConstantTo(CurrentRotation, OpenedRotation, ROTATION_INTERVAL, DOOR_SPEED);

		SetActorRotation(NewRotation);
	}
	else
	{
		if ((CurrentRotation - ClosedRotation).IsNearlyZero(0.001))
		{
			return;
		}

		FRotator NewRotation = Math::InterpConstantTo(CurrentRotation, ClosedRotation, ROTATION_INTERVAL, DOOR_SPEED);

		SetActorRotation(NewRotation);
	}

	FTimerHandle RotationHandle;
	GetWorld()->GetTimerManager().SetTimer(RotationHandle, this, &AGate::RotateGate, ROTATION_INTERVAL, false);
}