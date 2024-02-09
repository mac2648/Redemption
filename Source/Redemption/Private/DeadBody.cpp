// Fill out your copyright notice in the Description page of Project Settings.


#include "DeadBody.h"

// Sets default values
ADeadBody::ADeadBody()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body Mesh"));

}

// Called when the game starts or when spawned
void ADeadBody::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeadBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

