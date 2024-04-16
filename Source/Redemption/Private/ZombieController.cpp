// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieController.h"
#include "BehaviorTree/BlackboardComponent.h"

void AZombieController::StopAttack()
{
	if (UBlackboardComponent* BBComp = GetBlackboardComponent())
	{
		BBComp->SetValueAsBool("IsAttacking", false);
		UE_LOG(LogTemp, Warning, TEXT("StopAttacking"))
	}
}