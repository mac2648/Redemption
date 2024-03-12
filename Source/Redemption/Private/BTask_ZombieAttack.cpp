// Fill out your copyright notice in the Description page of Project Settings.

#include "BTask_ZombieAttack.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTask_ZombieAttack::UBTask_ZombieAttack()
{
	NodeName = "Zombie Attack";
}

EBTNodeResult::Type UBTask_ZombieAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		BBComp->SetValueAsBool(IsAttacking.SelectedKeyName, true);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}