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

	FTimerHandle StartCheckHandle;
	GetWorldTimerManager().SetTimer(StartCheckHandle, this, &APuzzlePressurePlate::FirstOverlapCheck, 1);
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

void APuzzlePressurePlate::FirstOverlapCheck()
{
	TArray<AActor*> OverlappingActors;
	BoxComp->GetOverlappingActors(OverlappingActors);

	UE_LOG(LogTemp, Warning, TEXT("%d"), OverlappingActors.IsEmpty());
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OverlappingActors[0]->GetName());

	for (AActor* Current : OverlappingActors)
	{
		if (Current != this)
		{
			IsActive = true;
			OnActivate.Broadcast();
			break;
		}
	}
}

void APuzzlePressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Deactivate();
}