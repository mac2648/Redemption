// Fill out your copyright notice in the Description page of Project Settings.


#include "PluzzeButton.h"
#include "Components/BoxComponent.h"

APluzzeButton::APluzzeButton()
{
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);

	Mesh->SetupAttachment(BoxComp);
}

void APluzzeButton::BeginPlay()
{
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &APluzzeButton::OnOverlapBegin);
}

void APluzzeButton::Activate()
{
	IsActive = true;

	OnActivate.Broadcast();
}

void APluzzeButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Activate();
}