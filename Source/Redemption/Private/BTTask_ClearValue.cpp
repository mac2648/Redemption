// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearValue::UBTTask_ClearValue()
{
	NodeName = "ClearValue";
}

EBTNodeResult::Type UBTTask_ClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent())
	{
		BBComp->ClearValue(GetSelectedBlackboardKey());
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}