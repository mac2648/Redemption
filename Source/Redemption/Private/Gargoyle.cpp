// Fill out your copyright notice in the Description page of Project Settings.

#include "Gargoyle.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AGargoyle::AGargoyle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Comp"));
	SetRootComponent(CapsuleComp);

	FloatMovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement Comp"));

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(CapsuleComp);
}

// Called when the game starts or when spawned
void AGargoyle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGargoyle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGargoyle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

