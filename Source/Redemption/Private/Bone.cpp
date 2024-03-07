// Fill out your copyright notice in the Description page of Project Settings.

#include "Bone.h"
#include "Components/BoxComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
ABone::ABone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABone::OnBoneBeginOverlap);

	BoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bone Mesh"));
	BoxComp->SetupAttachment(BoneMesh);

	SetRootComponent(BoneMesh);
	//changed the root component

	RotationComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation Comp"));
}

// Called when the game starts or when spawned
void ABone::BeginPlay()
{
	Super::BeginPlay();

	RotationComp->RotationRate = FRotator(-180.0, 0.0, 0.0);
}

// Called every frame
void ABone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//this function is triggered when the bone overlaps with something
void ABone::OnBoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}

	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		RotationComp->RotationRate = FRotator(0.0, 0.0, 0.0);
		UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.5f, this);

		SoundWave = GetWorld()->SpawnActor<AActor>(SoundWaveClass, GetActorLocation(), FRotator::ZeroRotator);

		FTimerHandle DestroyHandle;
		GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &ABone::DestroyBone, 2.0, false);

		FTimerHandle DestroyHandle2;
		GetWorld()->GetTimerManager().SetTimer(DestroyHandle2, this, &ABone::DestroySoundWave, 2.0, false);
	}
}

