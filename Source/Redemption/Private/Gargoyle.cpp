// Fill out your copyright notice in the Description page of Project Settings.

#include "Gargoyle.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "RedemptionPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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
	
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AGargoyle::OnOverlapBegin);
}

// Called every frame
void AGargoyle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AAIController* _Controller = Cast<AAIController>(GetController()))
	{
		IsLanded = _Controller->GetBlackboardComponent()->GetValueAsBool("IsLanded");
	}
}

// Called to bind functionality to input
void AGargoyle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int AGargoyle::GetStandingIndex(APatrolPathIndicator* Point) const
{
	for (int i = 0; i < StandingPoints.Num(); i++)
	{
		if (StandingPoints[i] == Point)
		{
			return i;
		}
	}

	return -1;
}

void AGargoyle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARedemptionPlayer* Player = Cast<ARedemptionPlayer>(OtherActor))
	{
		if (!Player->bIsCrouched)
		{
			UGameplayStatics::ApplyDamage(Player, 1.0f, GetController(), this, UDamageType::StaticClass());
		}
	}
}