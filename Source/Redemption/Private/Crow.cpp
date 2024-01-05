// Fill out your copyright notice in the Description page of Project Settings.

#include "Crow.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ACrow::ACrow()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsule component"));
	SetRootComponent(CapsuleComp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(CapsuleComp);

	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));
}

// Called when the game starts or when spawned
void ACrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACrow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

