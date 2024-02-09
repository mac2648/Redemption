// Fill out your copyright notice in the Description page of Project Settings.

#include "Rat.h"
#include "Components/CapsuleComponent.h"
#include "RedemptionPlayer.h"
#include "Kismet/GameplayStatics.h"

ARat::ARat()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Temporary mesh"));
	StaticMesh->SetupAttachment(GetCapsuleComponent());
}

void ARat::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ARat::OnOverlapBegin);
}

//function to deal damage to player when overlaping it
void ARat::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(OtherActor))
	{
		UGameplayStatics::ApplyDamage(Player, 1.0f, GetController(), this, UDamageType::StaticClass());
	}
}