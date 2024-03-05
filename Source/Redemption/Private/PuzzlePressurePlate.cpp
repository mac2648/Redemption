// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePressurePlate.h"
#include "Components/BoxComponent.h"

APuzzlePressurePlate::APuzzlePressurePlate()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BaseMesh->SetupAttachment(BoxComp);
	PuzzleMesh->SetupAttachment(BoxComp);
}

void APuzzlePressurePlate::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APuzzlePressurePlate::OnOverlapBegin);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &APuzzlePressurePlate::OnOverlapEnd);
}

void APuzzlePressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Activate();
}

void APuzzlePressurePlate::Deactivate()
{
	IsActive = false;

	//gate will check if all are active so it does not matter that it is deactivating
	OnActivate.Broadcast();
}

void APuzzlePressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Deactivate();
}