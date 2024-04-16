// Fill out your copyright notice in the Description page of Project Settings.

#include "BTask_ZombieAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ZombieController.h"

UBTask_ZombieAttack::UBTask_ZombieAttack()
{
	NodeName = "Zombie Attack";
}

EBTNodeResult::Type UBTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		BBComp->SetValueAsBool(IsAttacking.SelectedKeyName, true);
		BBComp->SetValueAsBool(IsStunned.SelectedKeyName, true);

		if (AZombieController* Controller = Cast<AZombieController>((OwnerComp.GetAIOwner())))
		{
			FTimerHandle StopAttackHandle;
			GetWorld()->GetTimerManager().SetTimer(StopAttackHandle, Controller, &AZombieController::StopAttack, 2.7);
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}