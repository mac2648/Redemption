// Fill out your copyright notice in the Description page of Project Settings.

#include "Bone.h"
#include "Components/BoxComponent.h"

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
}

// Called when the game starts or when spawned
void ABone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABone::OnBoneBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}