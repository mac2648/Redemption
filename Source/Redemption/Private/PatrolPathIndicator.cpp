// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPathIndicator.h"
#include "Components/ArrowComponent.h"

// Sets default values
APatrolPathIndicator::APatrolPathIndicator()
{
	PrimaryActorTick.bCanEverTick = false;

	Indicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Indicator"));
	SetRootComponent(Indicator);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Indicator);
}

// Called when the game starts or when spawned
void APatrolPathIndicator::BeginPlay()
{
	Super::BeginPlay();
	
	Indicator->SetVisibility(false, true);
	Arrow->SetVisibility(false);
}

// Called every frame
void APatrolPathIndicator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}