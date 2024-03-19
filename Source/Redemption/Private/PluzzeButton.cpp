// Fill out your copyright notice in the Description page of Project Settings.


#include "PluzzeButton.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstance.h"

APluzzeButton::APluzzeButton()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	BaseMesh->SetupAttachment(BoxComp);
}

void APluzzeButton::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APluzzeButton::OnOverlapBegin);
}

void APluzzeButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PuzzleMesh->SetMaterial(0, ActivateMaterial);
	Activate();
}