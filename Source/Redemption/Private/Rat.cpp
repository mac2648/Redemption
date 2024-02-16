// Fill out your copyright notice in the Description page of Project Settings.

#include "Rat.h"
#include "Components/CapsuleComponent.h"
#include "RedemptionPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ARat::ARat()
{

}

void ARat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AAIController* _Controller = Cast<AAIController>(GetController()))
	{
		if (_Controller->GetBlackboardComponent()->GetValueAsObject("Player"))
		{
			IsChasing = true;
		}
		else
		{
			IsChasing = false;
		}
	}
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

		FVector knockbackDir = Player->GetActorLocation() - GetActorLocation();
		knockbackDir.Normalize();

		Player->GetCharacterMovement()->Velocity = knockbackDir * 500;
	}
}